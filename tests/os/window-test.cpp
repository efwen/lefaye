#include <gtest/gtest.h>
#include <lf/os/window.hpp>

using namespace lf::os;

TEST(Window, Create) {
  Window w;
  bool result = w.create("Hello", 0, 0);
  ASSERT_EQ(result, true);
}

TEST(Window, IsOpen) {
  Window w;
  ASSERT_EQ(w.isOpen(), false);
  w.create("TestWindow", 640, 480);
  ASSERT_EQ(w.isOpen(), true);
  w.destroy();
  ASSERT_EQ(w.isOpen(), false);
}

TEST(Window, Destroy) {
  Window w;
  bool result = w.destroy();
  ASSERT_EQ(result, false);
  w.create("TestWindow", 640, 480);
  result = w.destroy();
  ASSERT_EQ(result, true);
}

TEST(Window, Update) {
  Window w;
  bool result = w.update();
  ASSERT_EQ(result, false);

  w.create("TestWindow", 640, 480);

  result = w.update();
  ASSERT_EQ(result, true);
}
