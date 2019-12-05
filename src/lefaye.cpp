#include "lf/lefaye.hpp"

#include <cstdio>
#include <vulkan/vulkan.h>

namespace lf {
  void init(uint32_t width, uint32_t height) {
  }

  void shutdown() {
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
