#include <cstdint>

namespace lf {
  void init(uint32_t width, uint32_t height);
  void shutdown();

  void printHello();
  bool update();

  int add_vals(int a, int b);
}
