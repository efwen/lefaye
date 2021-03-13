#include "lf/pch.hpp"
#include "lf/app.hpp"
#include "lf/util/log.hpp"
#include "lf/os/event_queue.hpp"
#include "lf/gfx.hpp"
#include "lf/os/window.hpp"
#include "lf/os/file.hpp"

namespace lf {
  //forward declarations
  void init(const char* title, uint32_t width, uint32_t height);
  void update();
  void shutdown();

  os::Window window;
  os::File file;

  bool running = true; 

  void run(App& app, const char* title, uint32_t window_width, uint32_t window_height) {
    init(title, window_width, window_height);
    app.init();

    while(running) {
      update();
      app.update();
    }

    app.shutdown();
    shutdown();
  }

  void init(const char* title, uint32_t width, uint32_t height) {
    log::init();
    log::info("Initializing LeFaye. Title: {}, Screen is {}x{}",
        title, width, height);

    os::event_queue.addListener(os::EventType::kShutdown, [](os::Event& e) {
      log::info("Shutdown Requested...");
      running = false;
    });

    os::event_queue.addListener(os::EventType::kWindowClose, [](os::Event& e) {
      log::info("Window closed!");
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
      fmt::print("\n");
    }

    window.create(title, width, height);
    uint32_t result = gfx::init(title);
  }

  void update() {
    window.update();
    os::event_queue.dispatchEvents();
    gfx::draw();
  }

  void shutdown() {
    log::info("Shutting Down LeFaye...");
    file.close();
    gfx::shutdown();
    window.destroy();
  }

}
