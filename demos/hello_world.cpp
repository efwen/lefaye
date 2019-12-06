#include <fmt/format.h>
#include <lf/lefaye.hpp>

int main(int, char**) {
  fmt::print("Hello World!\n");
  lf::init(640, 480);

  bool running = true;
  while(running) {
    if(!lf::updateWindow()) {
      running = false;
    }
  }

  lf::shutdown();
  return 0;
}
