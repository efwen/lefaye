#include <lf/lefaye.hpp>

int main(int, char**) {
  lf::init(1280, 720);
  lf::printHello();

  bool running = true;
  while(running) {
    if(!lf::updateWindow()) {
      running = false;
    }
  }

  lf::shutdown();
  return 0;
}
