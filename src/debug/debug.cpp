#include "../include/debug.h"
#include <string>

// namespace debug {
UnityDebugCallback unityDebugCallback = nullptr;
DebugCallback debugCallback = nullptr;

void log(const char *msg) {
  if (unityDebugCallback != nullptr) {
    unityDebugCallback(msg);
  }
  if (debugCallback != nullptr) {
    debugCallback(msg);
  }
}
void log(std::string &msg) { log(msg.c_str()); }
//} // namespace debug