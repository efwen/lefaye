#include "lf/pch.hpp"
#include "lf/app.hpp"
#include "lf/util/log.hpp"
#include "lf/util/log_internal.hpp"
#include "lf/events/event_queue.hpp"
#include "lf/gfx.hpp"
#include "lf/os/window.hpp"

namespace lf {
  //forward declarations
  void init(App& app);
  void main_loop(App& app);
  void shutdown(App& app);

  os::Window window;

  void run(std::unique_ptr<App> app) {
    //Initialization
    init(*app);

    //Main Loop
    main_loop(*app);

    //Shutdown
    shutdown(*app);
  }

  void init(App& app) {
    auto boot_props = app.getBootProps();

    log::init(boot_props.title);
    log::internal::info("Initializing LeFaye");

    window.create(boot_props.title, boot_props.window_width, boot_props.window_height);
    uint32_t result = gfx::init(boot_props.title);
    app.init();
  }

  void main_loop(App& app) {
    bool running = true;

    event_queue.addCallback(EventType::kShutdown, [&running](const Event& e) {
      log::internal::info("Shutdown Requested...");
      running = false;
    });

    event_queue.addCallback(EventType::kWindowClose, [](const Event& e) {
      if(MessageBoxA(NULL, "Close Application?", "Close Application?", MB_OKCANCEL) == IDCANCEL)
        return;
      
      Event event;
      event.type = EventType::kShutdown;
      event_queue.pushEvent(event);
    });


    while(running) {
      window.update();
      event_queue.dispatchEvents();
      app.update();
      gfx::draw();
    }
  }

  void shutdown(App& app) {
    log::internal::info("Shutting Down LeFaye...");
    app.shutdown();
    gfx::shutdown();
    window.destroy();
  }

}
