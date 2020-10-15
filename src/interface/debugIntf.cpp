#include "../include/debugIntf.h"
#include "../include/debug.h"

void registerUnityDbgCallback(UnityDebugCallback callback) {
  if (callback != nullptr) {
    unityDebugCallback = callback;
  }
}

void registerDebugCallback(DebugCallback callback) {
  if (callback != nullptr) {
    debugCallback = callback;
  }
}