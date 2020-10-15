#include "../include/debugIntf.h"
#include "../include/debug.h"

void registerUnityDbgCallback(UnityDebugCallback callback) {
  unityDebugCallback = callback;
  if (callback != nullptr) {
  }
}

void registerDebugCallback(DebugCallback callback) {
  debugCallback = callback;
  if (callback != nullptr) {
  }
}