#pragma once

#include <cstdint>

namespace lf::os {

  void createWindow(uint32_t width, uint32_t height);
  void destroyWindow();
  bool updateWindow();
}
