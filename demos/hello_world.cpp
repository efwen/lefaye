#include <memory>

#include <lf/lefaye.hpp>
#include <lf/events/event_queue.hpp>
#include <lf/util/log.hpp>

class HelloApp : public lf::App {
public:
  HelloApp(const BootProperties& props) : App(props) {}

  void init() {
    lf::log::info("HelloApp Setup");

    lf::event_queue.addCallback(lf::EventType::kKeyPressed, [this](const lf::Event& e){
      lf::log::trace("{} key pressed! Frame {}", e.key_code, frame_count);

      if(e.key_code == 27) {    //escape key triggers shutdown
        lf::Event shutdown_event;
        shutdown_event.type = lf::EventType::kShutdown;
        lf::event_queue.pushEvent(shutdown_event);
      }
    });
  }

  void update() {
    frame_count++;
  }

  void shutdown() {
    lf::log::info("HelloApp Shutdown!");
  }
private:
  uint64_t frame_count = 0;
};


int main(int, char**) {
  lf::App::BootProperties props {
    "HelloApp",
    1280, 720
  };

  lf::run(std::make_unique<HelloApp>(props));
  return 0;
}
