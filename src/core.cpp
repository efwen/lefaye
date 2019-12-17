#include "lf/lefaye.hpp"
#include "lf/log.hpp"
#include "lf/os/window.hpp"
#include "lf/os/file.hpp"
#include "lf/gfx.hpp"

#include <cstdio>

namespace lf {
  os::File file;

  void init(const char* title, uint32_t width, uint32_t height) {
    log::info("Initializing LeFaye. Title: {}, Screen is {}x{}",
        title, width, height);

    file.open("hello.txt", os::FileOpenMode::kRead);

    char buf[256];
    memset(buf, 0, 256);

    while(file.read(buf, 256).second > 0) {
      fmt::print(buf);
    }

    os::createWindow(title, width, height);
    uint32_t result = gfx::init(title);
  }

  void shutdown() {
    file.close();
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