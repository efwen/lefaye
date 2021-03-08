#pragma once
#include <cstdint>

namespace lf {
  void init(const char* title, uint32_t width, uint32_t height);
  bool update();
  void shutdown();
}
