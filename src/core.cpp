#include "lf/pch.hpp"
#include "lf/lefaye.hpp"
#include "lf/util/log.hpp"
#include "lf/os/event_queue.hpp"
#include "lf/gfx.hpp"
#include "lf/os/window.hpp"
#include "lf/os/file.hpp"

#include "lf/gfx.hpp"

namespace lf {
  os::Window window;
  os::File file;

  bool quit = false;

  void init(const char* title, uint32_t width, uint32_t height) {
    log::init();
    log::info("Initializing LeFaye. Title: {}, Screen is {}x{}",
        title, width, height);

    os::event_queue.addListener(os::EventType::kShutdown, [](os::Event& e) {
      log::warn("Shutdown Requested...");
      quit = true;
    });

    os::event_queue.addListener(os::EventType::kWindowClose, [](os::Event& e) {
      log::warn("Window closed!");
      os::Event event;
      event.type = os::EventType::kShutdown;
      os::event_queue.pushEvent(event);
    });

    if(file.open("data/hello.txt", os::FileOpenMode::kRead)) {
      char buf[256];
      memset(buf, 0, sizeof(buf));

      while(file.read(buf, 256).second > 0) {
        fmt::print(buf);
      }
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
    window.update();
    os::event_queue.processEvents();
    gfx::draw();

    return !quit;
  }
}
