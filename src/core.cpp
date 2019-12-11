#include "lf/lefaye.hpp"
#include "lf/int/log.hpp"
#include "lf/int/os.hpp"
#include "lf/gfx.hpp"

#include <cstdio>

namespace lf {
  void init(const char* title, uint32_t width, uint32_t height) {
    log::info("This is an info log. Screen is {}x{}", width, height);
    log::warn("This is a warning. Screen is {}x{}", width, height);
    log::error("This is an error. Screen is {}x{}", width, height);
    os::createWindow(title, width, height);
    uint32_t result = gfx::init(title);
  }

  void shutdown() {
    gfx::shutdown();
    os::destroyWindow();
  }

  bool update() {
    if(!os::updateWindow())
      return false;

    gfx::draw();

     return true;
  }

  int add_vals(int a, int b) {
    return a + b;
  }
}
