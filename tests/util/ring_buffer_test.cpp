#include <gtest/gtest.h>
#include <lf/util/ring_buffer.hpp>

using namespace lf::util;

TEST(RingBuffer, InitialState) {
  RingBuffer<int, 24> buf;

  ASSERT_EQ(buf.getCapacity(), 24);
  ASSERT_EQ(buf.getSize(), 0);
  ASSERT_EQ(buf.isEmpty(), true);
}

TEST(RingBuffer, Push) {
  ASSERT_EQ(true, false);
}

TEST(RingBuffer, Pop) {
  ASSERT_EQ(true, false);
}

TEST(RingBuffer, Peek) {
  ASSERT_EQ(true, false);
}

TEST(RingBuffer, getCapacity) {
  ASSERT_EQ(true, false);
}

TEST(RingBuffer, getSize) {
  ASSERT_EQ(true, false);
}

TEST(RingBuffer, isEmpty) {
  ASSERT_EQ(true, false);
}
