#pragma once
#include <cstdint>

namespace lf::gfx {
  uint32_t init(const char* title);
  void shutdown();
  void draw();
}
