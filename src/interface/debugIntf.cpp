#include "../include/debugIntf.h"

#include <iostream>

#include "../include/debug.h"

void registerUnityDbgCallback( merci::debug::UnityDebugCallback callback ) {
    if ( callback != nullptr ) {
        merci::debug::unityDebugCallback = callback;
        std::cout << "Added Unity debug callback" << std::endl;
    }
}

void registerDebugCallback( merci::pFnVoidStr callback ) {
    if ( callback != nullptr ) {
        merci::debug::debugCallback = callback;
        std::cout << "Added debug callback: " << merci::debug::debugCallback
                  << std::endl;
    }
}