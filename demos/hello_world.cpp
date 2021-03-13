
#include <iostream>
#include <lf/lefaye.hpp>
#include <lf/os/event_queue.hpp>

class HelloApp : public lf::App {
public:
  void init() {
    std::cout << "HelloApp Setup" << std::endl;

    lf::os::event_queue.addListener(lf::os::EventType::kKeyPressed, [this](lf::os::Event& e){
      std::cout << e.key_code << " key pressed! Frame " << frame_count << std::endl;

      if(e.key_code == 27) {    //escape key triggers shutdown
        lf::os::Event shutdown_event;
        shutdown_event.type = lf::os::EventType::kShutdown;
        lf::os::event_queue.pushEvent(shutdown_event);
      }
    });
  }

  void update() {
    frame_count++;
  }

  void shutdown() {
    std::cout << "HelloApp Shutdown!" << std::endl;
  }
private:
  uint64_t frame_count = 0;
};


int main(int, char**) {
  HelloApp hello_app;
  lf::run(hello_app, "HelloApp", 1280, 720);
  return 0;
}
