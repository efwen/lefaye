#pragma once
#include <cstdint>

namespace lf::gfx {
  uint32_t init(std::string_view title);
  void shutdown();
  void draw();
}
