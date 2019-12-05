#include <fmt/format.h>
#include <lf/lefaye.hpp>

int main(int, char**) {
  fmt::print("Hello World!\n");

  fmt::print("{} vulkan extensions supported\n", lf::getVulkanExtensionCount());

  return 0;
}
