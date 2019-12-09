#include "lf/lefaye.hpp"
#include "lf/int/os.hpp"

#include <cstdio>
#include <vulkan/vulkan.h>
#include <fmt/format.h>

namespace lf {

  void init(uint32_t width, uint32_t height) {
     os::createWindow(width, height);
  }

  void shutdown() {
    os::destroyWindow();
  }

  bool update() {
    if(!os::updateWindow())
      return false;

     return true;
  }

  void printHello() {
    fmt::print("Hello from lefaye!\n");
  }

  uint32_t getVulkanExtensionCount() {
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    return extensionCount;
  }

  int add_vals(int a, int b) {
    return a + b;
  }
}
