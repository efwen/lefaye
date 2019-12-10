#include "lf/lefaye.hpp"
#include "lf/int/os.hpp"
#include "lf/gfx.hpp"

#include <cstdio>

namespace lf {
  void init(const char* title, uint32_t width, uint32_t height) {
    os::createWindow(title, width, height);
    gfx::init();
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
