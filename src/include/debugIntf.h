#pragma once
#include "../common/exported.h"
#include "debug.h"

extern "C" {
/**
 * @brief Register a callback from Unity or any other non C/C++ application to
 * receive string messages for debugging
 *
 * @param callback
 * @return void
 */
EXPORTED void registerUnityDbgCallback(
    merci::debug::UnityDebugCallback callback );

/**
 * @brief Register a callback from an external C/C++ application to receive
 * string messages for debugging
 *
 * @param callback
 * @return void
 */
EXPORTED void registerDebugCallback( merci::debug::DebugCallback callback );
}