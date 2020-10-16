#pragma once
#include "../common/exported.h"
#include <string>

// namespace debug {
/**
 * @brief Define callback types for external C/C++ and non C/C++ applications to
 * help with debug messages
 *
 */
#ifdef _WIN32
// This allows us to receive callback functions from Unity
using UnityDebugCallback = void __stdcall (*)(const char *str);
// typedef void(__stdcall *UnityDebugCallback)(const char *str);
#else
// This allows us to receive callback functions from Unity
using UnityDebugCallback = void (*)(const char *str);
#endif
// This allows us to receive callback functions from other C/C++ applications
using DebugCallback = void (*)(const char *str);
// typedef void (*DebugCallback)(const char *str);

/**
 * @brief Standard log function
 *
 * @param msg String type
 */
EXPORTED void log(const std::string &msg);

/**
 * @brief Standard log function
 *
 * @param msg char* type
 */
EXPORTED void log(const char *msg);

extern UnityDebugCallback unityDebugCallback;
extern DebugCallback debugCallback;
//} // namespace debug