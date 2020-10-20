#ifdef _WIN32
    #include <windows.h>
    #include <stdio.h>
    #include <intrin.h>
    #include <dbghelp.h>

    #include <vector>

//#pragma comment( lib, "dbghelp.lib" )
#else
    #include <cxxabi.h>              // __cxa_demangle
    #include <elfutils/libdwfl.h>    // Dwfl*
    #include <execinfo.h>            // backtrace
    #include <unistd.h>              // getpid

    #include <cassert>
    #include <iostream>
    #include <memory>
#endif

#include <sstream>
#include <string>

#include "../include/memory.h"

#ifdef _WIN32
inline std::string basename( const std::string& file ) {
    unsigned int i = file.find_last_of( "\\/" );
    if ( i == std::string::npos ) {
        return file;
    } else {
        return file.substr( i + 1 );
    }
}

struct StackFrame {
    DWORD64 address;
    std::string name;
    std::string module;
    unsigned int line;
    std::string file;
};

inline std::vector<StackFrame> stack_trace() {
    #if _WIN64
    DWORD machine = IMAGE_FILE_MACHINE_AMD64;
    #else
    DWORD machine = IMAGE_FILE_MACHINE_I386;
    #endif
    HANDLE process = GetCurrentProcess();
    HANDLE thread  = GetCurrentThread();

    if ( SymInitialize( process, NULL, TRUE ) == FALSE ) {
        return std::vector<StackFrame>();
    }

    SymSetOptions( SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS );

    CONTEXT context      = {};
    context.ContextFlags = CONTEXT_FULL;
    RtlCaptureContext( &context );

    #if _WIN64
    STACKFRAME frame       = {};
    frame.AddrPC.Offset    = context.Rip;
    frame.AddrPC.Mode      = AddrModeFlat;
    frame.AddrFrame.Offset = context.Rbp;
    frame.AddrFrame.Mode   = AddrModeFlat;
    frame.AddrStack.Offset = context.Rsp;
    frame.AddrStack.Mode   = AddrModeFlat;
    #else
    STACKFRAME frame       = {};
    frame.AddrPC.Offset    = context.Eip;
    frame.AddrPC.Mode      = AddrModeFlat;
    frame.AddrFrame.Offset = context.Ebp;
    frame.AddrFrame.Mode   = AddrModeFlat;
    frame.AddrStack.Offset = context.Esp;
    frame.AddrStack.Mode   = AddrModeFlat;
    #endif

    bool first = true;

    std::vector<StackFrame> frames;
    while ( StackWalk( machine, process, thread, &frame, &context, NULL,
                       SymFunctionTableAccess, SymGetModuleBase, NULL ) ) {
        StackFrame f = {};
        f.address    = frame.AddrPC.Offset;

    #if _WIN64
        DWORD64 moduleBase = 0;
    #else
        DWORD moduleBase = 0;
    #endif

        moduleBase = SymGetModuleBase( process, frame.AddrPC.Offset );

        char moduelBuff[MAX_PATH];
        if ( moduleBase && GetModuleFileNameA( (HINSTANCE)moduleBase,
                                               moduelBuff, MAX_PATH ) ) {
            f.module = basename( moduelBuff );
        } else {
            f.module = "Unknown Module";
        }
    #if _WIN64
        DWORD64 offset = 0;
    #else
        DWORD offset = 0;
    #endif
        char symbolBuffer[sizeof( IMAGEHLP_SYMBOL ) + 255];
        PIMAGEHLP_SYMBOL symbol = (PIMAGEHLP_SYMBOL)symbolBuffer;
        symbol->SizeOfStruct    = ( sizeof( IMAGEHLP_SYMBOL ) ) + 255;
        symbol->MaxNameLength   = 254;

        if ( SymGetSymFromAddr( process, frame.AddrPC.Offset, &offset,
                                symbol ) ) {
            f.name = symbol->Name;
        } else {
            DWORD error = GetLastError();
            f.name      = "Unknown Function";
        }

        IMAGEHLP_LINE line;
        line.SizeOfStruct = sizeof( IMAGEHLP_LINE );

        DWORD offset_ln = 0;
        if ( SymGetLineFromAddr( process, frame.AddrPC.Offset, &offset_ln,
                                 &line ) ) {
            f.file = line.FileName;
            f.line = line.LineNumber;
        } else {
            DWORD error = GetLastError();
            f.line      = 0;
        }

        if ( !first ) { frames.push_back( f ); }
        first = false;
    }

    SymCleanup( process );

    return frames;
}

std::string stacktrace_windows() {
    std::stringstream buff;
    std::vector<StackFrame> stack = stack_trace();
    for ( unsigned int i = 0; i < stack.size(); i++ ) {
        buff << "0x" << std::hex << stack[i].address << ": " << stack[i].name
             << "(" << stack[i].line << ") in " << stack[i].module << "\n";
    }
    return buff.str();
}
#else
// https://stackoverflow.com/questions/281818/unmangling-the-result-of-stdtype-infoname
std::string demangle( const char* name ) {
    int status = -4;
    std::unique_ptr<char, void ( * )( void* )> res{
        abi::__cxa_demangle( name, NULL, NULL, &status ), std::free
    };
    return ( status == 0 ) ? res.get() : name;
}

std::string debug_info( Dwfl* dwfl, void* ip ) {
    std::string function;
    int line = -1;
    char const* file;
    uintptr_t ip2       = reinterpret_cast<uintptr_t>( ip );
    Dwfl_Module* module = dwfl_addrmodule( dwfl, ip2 );
    char const* name    = dwfl_module_addrname( module, ip2 );
    function            = name ? demangle( name ) : "<unknown>";
    if ( Dwfl_Line* dwfl_line = dwfl_module_getsrc( module, ip2 ) ) {
        Dwarf_Addr addr;
        file =
            dwfl_lineinfo( dwfl_line, &addr, &line, nullptr, nullptr, nullptr );
    }
    std::stringstream ss;
    ss << ip << ' ' << function;
    if ( file ) ss << " at " << file << ':' << line;
    ss << std::endl;
    return ss.str();
}

std::string stacktrace_linux() {
    // Initialize Dwfl.
    Dwfl* dwfl = nullptr;
    {
        Dwfl_Callbacks callbacks = {};
        char* debuginfo_path     = nullptr;
        callbacks.find_elf       = dwfl_linux_proc_find_elf;
        callbacks.find_debuginfo = dwfl_standard_find_debuginfo;
        callbacks.debuginfo_path = &debuginfo_path;
        dwfl                     = dwfl_begin( &callbacks );
        assert( dwfl );
        int r;
        r = dwfl_linux_proc_report( dwfl, getpid() );
        assert( !r );
        r = dwfl_report_end( dwfl, nullptr, nullptr );
        assert( !r );
        static_cast<void>( r );
    }

    // Loop over stack frames.
    std::stringstream ss;
    {
        void* stack[512];
        int stack_size = ::backtrace( stack, sizeof stack / sizeof *stack );
        for ( int i = 0; i < stack_size; ++i ) {
            ss << i << ": ";

            // Works.
            ss << debug_info( dwfl, stack[i] );

    #if 0
            // TODO intended to do the same as above, but segfaults,
            // so possibly UB In above function that does not blow up by chance?
            void *ip = stack[i];
            std::string function;
            int line = -1;
            char const* file;
            uintptr_t ip2 = reinterpret_cast<uintptr_t>(ip);
            Dwfl_Module* module = dwfl_addrmodule(dwfl, ip2);
            char const* name = dwfl_module_addrname(module, ip2);
            function = name ? demangle(name) : "<unknown>";
            // TODO if I comment out this line it does not blow up anymore.
            if (Dwfl_Line* dwfl_line = dwfl_module_getsrc(module, ip2)) {
              Dwarf_Addr addr;
              file = dwfl_lineinfo(dwfl_line, &addr, &line, nullptr, nullptr, nullptr);
            }
            ss << ip << ' ' << function;
            if (file)
                ss << " at " << file << ':' << line;
            ss << std::endl;
    #endif
        }
    }
    dwfl_end( dwfl );
    return ss.str();
}
#endif

namespace merci {
    namespace memory {
#ifdef _WIN32
        pFnStrVoid getStackTrace = ::stacktrace_windows;
#else
        pFnStrVoid getStackTrace = ::stacktrace_linux;
#endif
    }    // namespace memory
}    // namespace merci

/*

void my_func_2() {
    std::cout << stacktrace() << std::endl;
    std::cout.flush();
}

void my_func_1( double f ) {
    (void)f;
    my_func_2();
}

void my_func_1( int i ) {
    (void)i;
    my_func_2();
}

int main( int argc, char** argv ) {
    long long unsigned int n;
    if ( argc > 1 ) {
        n = strtoul( argv[1], NULL, 0 );
    } else {
        n = 1;
    }
    for ( long long unsigned int i = 0; i < n; ++i ) {
        my_func_1( 1 );
        my_func_1( 2.0 );
    }
}
*/