#include "lf/pch.hpp"
#include "lf/app.hpp"
#include "lf/util/log.hpp"
#include "lf/os/event_queue.hpp"
#include "lf/gfx.hpp"
#include "lf/os/window.hpp"

namespace lf {
  //forward declarations
  void init(App& app, const char* title, uint32_t width, uint32_t height);
  void main_loop(App& app);
  void shutdown(App& app);

  os::Window window;

  void run(App& app, const char* title, uint32_t window_width, uint32_t window_height) {
    //Initialization
    init(app, title, window_width, window_height);

    //Main Loop
    main_loop(app);

    //Shutdown
    shutdown(app);
  }

  void init(App& app, const char* title, uint32_t window_width, uint32_t window_height) {
    log::init();
    log::info("Initializing LeFaye");

    window.create(title, window_width, window_height);
    uint32_t result = gfx::init(title);
    app.init();
  }

  void main_loop(App& app) {
    bool running = true;

    os::event_queue.addListener(os::EventType::kShutdown, [&running](os::Event& e) {
      log::info("Shutdown Requested...");
      running = false;
    });

    os::event_queue.addListener(os::EventType::kWindowClose, [](os::Event& e) {
      if(MessageBoxA(NULL, "Close Application?", "Close Application?", MB_OKCANCEL) == IDCANCEL)
        return;
      
      log::info("Window closed!");
      os::Event event;
      event.type = os::EventType::kShutdown;
      os::event_queue.pushEvent(event);
    });


    while(running) {
      window.update();
      os::event_queue.dispatchEvents();
      app.update();
      gfx::draw();
    }
  }

  void shutdown(App& app) {
    log::info("Shutting Down LeFaye...");
    app.shutdown();
    gfx::shutdown();
    window.destroy();
  }

}
