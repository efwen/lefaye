#include <cstdint>

namespace lf {
  void init(const char* title, uint32_t width, uint32_t height);
  void shutdown();
  bool update();

  int add_vals(int a, int b);
}
