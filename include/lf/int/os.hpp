#pragma once

#include <cstdint>

namespace lf::os {

  void createWindow(const char* name, uint32_t width, uint32_t height);
  void destroyWindow();
  bool updateWindow();
}
