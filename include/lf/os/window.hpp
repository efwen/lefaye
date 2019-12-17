#pragma once
#include <cstdint>

#ifdef LF_WIN32
  #include <windows.h>
#endif

namespace lf::os {
  void createWindow(const char* title, uint32_t width, uint32_t height);
  void destroyWindow();
  bool updateWindow();
}
