#include <lf/lefaye.hpp>

int main(int, char**) {
  lf::init("Hello World", 1280, 720);

  bool running = true;
  while(running) {
    if(!lf::update()) {
      running = false;
    }
  }

  lf::shutdown();
  return 0;
}
