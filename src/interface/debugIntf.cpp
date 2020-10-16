#include "../include/debugIntf.h"
#include "../include/debug.h"
#include <iostream>

void registerUnityDbgCallback(UnityDebugCallback callback) {
  if (callback != nullptr) {
    unityDebugCallback = callback;
    std::cout << "Added Unity debug callback" << std::endl;
  }
}

void registerDebugCallback(DebugCallback callback) {
  if (callback != nullptr) {
    debugCallback = callback;
    std::cout << "Added debug callback: " << debugCallback << std::endl;
  }
}