#include <gtest/gtest.h>
#include <lf/lefaye.hpp>

TEST(lf, example_test)
{
  uint32_t result;
  result = lf::getVulkanExtensionCount();
  ASSERT_GT(result, 0);
}

TEST(lf, add_vals)
{
  int a = 2;
  int b = 3;
  int result = lf::add_vals(a, b);
  ASSERT_EQ(result, a + b);
}
