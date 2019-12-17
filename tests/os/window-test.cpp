#include <gtest/gtest.h>
#include <lf/os/window.hpp>

using namespace lf::os;

TEST(window, constructor) {
 createWindow("Hello World", 640, 480);
 destroyWindow();
}
