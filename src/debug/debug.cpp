#include "../include/debug.h"
#include <string>

// namespace debug {
UnityDebugCallback unityDebugCallback = nullptr;
DebugCallback debugCallback = nullptr;

void log(const char *msg) {
  unityDebugCallback(msg);
  if (unityDebugCallback != nullptr) {
  }
  debugCallback(msg);
  if (debugCallback != nullptr) {
  }
}
void log(std::string &msg) { log(msg.c_str()); }
//} // namespace debug