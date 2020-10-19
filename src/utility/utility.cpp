#include "../common/utility.h"

#include <stdio.h>

#include <cmath>

#if defined _WIN32
    #define SPRINTF ::sprintf_s
#else
    #define SPRINTF ::snprintf
#endif

namespace merci {
    namespace utility {
        unsigned UpperPowerOfTwo( unsigned v ) {
            --v;
            v |= v >> 1;
            v |= v >> 2;
            v |= v >> 4;
            v |= v >> 8;
            v |= v >> 16;
            ++v;
            return v;
        }

        unsigned Round( float number ) {
            return number < 0.0f ? ::ceil( number - 0.5f )
                                 : ::floor( number + 0.5f );
        }

        const unsigned len = 256;
        char mem_buff[len];
        Cstr MemSizeToText( size_t size ) {
            double s = size;
            if ( size < 1024 ) {
                SPRINTF( mem_buff, len, "%d Bytes", (unsigned)size );
            } else if ( size < ( 1024 * 1024 ) ) {
                size /= 1024;
                SPRINTF( mem_buff, len, "%d KB", (unsigned)size );
            } else if ( size < ( 1024 * 1024 * 1024 ) ) {
                s /= ( 1024.0 * 1024.0 );
                SPRINTF( mem_buff, len, "%4.4f MB", s );
            } else {
                s /= ( 1024.0 * 1024.0 * 1024.0 );
                SPRINTF( mem_buff, len, "%6.6f GB", s );
            }
            //
            return mem_buff;
        }
    }    // namespace utility
}    // namespace merci