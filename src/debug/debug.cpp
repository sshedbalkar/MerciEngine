#include "../include/debug.h"

#include <iostream>
#include <string>

namespace merci {
    namespace debug {
        UnityDebugCallback unityDebugCallback;
        DebugCallback debugCallback;

        void log( const char *msg ) {
            if ( unityDebugCallback != nullptr ) {
                std::cout << "Calling Unity debug callback" << std::endl;
                unityDebugCallback( msg );
            }
            std::cout << "log debug callback: " << debugCallback << std::endl;
            if ( debugCallback != nullptr ) {
                std::cout << "Calling debug callback" << std::endl;
                debugCallback( msg );
            } else {
                std::cout << "Calling Debug callback but it is null"
                          << std::endl;
            }
        }
        void log( std::string &msg ) { log( msg.c_str() ); }
    }    // namespace debug
}    // namespace merci