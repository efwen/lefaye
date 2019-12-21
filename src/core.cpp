#include "lf/pch.hpp"
#include "lf/lefaye.hpp"
#include "lf/log.hpp"
#include "lf/gfx.hpp"
#include "lf/os/window.hpp"
#include "lf/os/file.hpp"

namespace lf {
  os::File file;
  os::Window window;

  void init(const char* title, uint32_t width, uint32_t height) {
    log::init();
    log::info("Initializing LeFaye. Title: {}, Screen is {}x{}",
        title, width, height);

    file.open("hello.txt", os::FileOpenMode::kRead);

    char buf[256];
    memset(buf, 0, 256);

    while(file.read(buf, 256).second > 0) {
      fmt::print(buf);
    }

    window.create(title, width, height);
    uint32_t result = gfx::init(title);
  }

  void shutdown() {
    file.close();
    gfx::shutdown();
    window.destroy();
  }

  bool update() {
    if(!window.update())
      return false;

    gfx::draw();
    return true;
  }
}
