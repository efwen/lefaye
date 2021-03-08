#include <gtest/gtest.h>
#include <lf/util/ring_buffer.hpp>

#include <limits>

using namespace lf::util;

TEST(RingBuffer, InitialState) {
  RingBuffer<int, 24> buf;

  ASSERT_EQ(buf.getCapacity(), 24);
  ASSERT_EQ(buf.getSize(), 0);
  ASSERT_EQ(buf.isEmpty(), true);
}

TEST(RingBuffer, Push) {
  RingBuffer<int, 10> buf;
  for(int i = 0; i < 10; i++) {
    bool success = buf.push(i);
    ASSERT_EQ(success, true) << "While not at capacity, push should succeed";
    ASSERT_EQ(buf.getSize(), i + 1) << "While successful, size should increment";
  }

  bool success = buf.push(11);
  ASSERT_EQ(success, false);
  ASSERT_EQ(buf.isFull(), true);
  ASSERT_EQ(buf.getSize(), 10);
}

TEST(RingBuffer, Pop) {
  RingBuffer<int, 10> buf;
  for(int i = 0; i < 10; i++) {
    buf.push(i);
  }

  for(int i = 10; i > 0; i--) {
    bool result = buf.pop();
    ASSERT_EQ(result, true) << "While not empty, pop should succeed";
    ASSERT_EQ(buf.getSize(), i - 1) << "When pop is successful, size should decrement";
  }

  int item = -1;
  bool result = buf.pop(item);
  ASSERT_EQ(result, false) << "Should not be able to pop more than capacity";
  ASSERT_EQ(buf.isEmpty(), true) << "Buffer should report empty on failure";
  ASSERT_EQ(item, -1) << "Item should not be assigned in pop failure";

  result = buf.pop();
  ASSERT_EQ(result, false) << "Should not be able to pop more than capacity";
  ASSERT_EQ(buf.isEmpty(), true) << "Buffer should report empty on failure";
}

TEST(RingBuffer, Peek) {
  RingBuffer<int, 10> buf;
  for(int i = 0; i < 10; i++) {
    bool success = buf.push(i);
    ASSERT_EQ(success, true);

    int item;
    ASSERT_EQ(buf.getSize(), i + 1);
    success = buf.peek(item);
    ASSERT_EQ(success, true) << "peek should report success while buffer is not empty. iteeration: " << i;
    ASSERT_EQ(buf.getSize(), i + 1) << "Buffer Size should not change when peeking!";
    ASSERT_EQ(item, 0) << "Peek value should remain as the last unpopped value";
  }

  for(int i = 0; i < 10; i++) {
    int item = -1;

    int peek_val = -1;
    int buf_size = buf.getSize();
    int success = buf.peek(peek_val);
    ASSERT_EQ(success, true) << "peek should report success while buffer is not empty";
    ASSERT_EQ(buf_size, buf.getSize()) << "size should not change when calling peek";
    ASSERT_EQ(peek_val, i) << "peek value should be last unpopped value";

    buf.pop();
  }
}

TEST(RingBuffer, WraparoundConsistency) {
  RingBuffer<int, 10> buf;

  //push 5 items [0 - 4]
  for(int i = 0; i < 5; i++) {
    buf.push(i);
  }

  //pop 3 items
  for(int i = 0; i < 3; i++) {
    buf.pop();
  }

  //peek should show [3]
  int item = -1;
  bool result = buf.peek(item);
  ASSERT_EQ(result, true);
  ASSERT_EQ(item, 3);

  //we should be able to push 8 more items
  for(int i = 5; i < 13; i++) {
      bool result = buf.push(i);
    ASSERT_EQ(result, true) << "Failed to push [" << i << "]";
  }

  //should be full at this point
  ASSERT_EQ(buf.isFull(), true);

  //pop the rest of the items from the buffer, should come as [3 - 12]
  for(int i = 3; i < 13; i++) {
    bool result = buf.pop();
    ASSERT_EQ(result, true);
  }

  ASSERT_EQ(buf.isEmpty(), true);
}

TEST(RingBuffer, getCapacity) {
  RingBuffer<int, 1> one;
  ASSERT_EQ(one.getCapacity(), 1);
  RingBuffer<int, 4> four;
  ASSERT_EQ(four.getCapacity(), 4);
}

TEST(RingBuffer, getSize) {
  RingBuffer<int, 10> buf;
  for(int i = 1; i <= 10; i++) {
    buf.push(i);
    ASSERT_EQ(buf.getSize(), i);
  }

  for(int i = 10; i > 0; i--) {
    buf.pop();
    ASSERT_EQ(buf.getSize(), i - 1);
  }

  RingBuffer<int, 10> offsetBuf;
  for(int i = 0; i < 10; i++) {
    buf.push(i);
  }

  ASSERT_EQ(buf.getSize(), 10);

  for(int i = 0; i < 4; i++) {
    buf.pop();
  }

  ASSERT_EQ(buf.getSize(), 6);

  for(int i = 6; i < 10; i++) {
    buf.push(i);
    ASSERT_EQ(buf.getSize(), i + 1);
  }
}

TEST(RingBuffer, isEmpty) {
  RingBuffer<int, 10> buf;

  ASSERT_EQ(buf.isEmpty(), true);

  buf.push(0);
  ASSERT_EQ(buf.isEmpty(), false);

  for(int i = 1; i < 10; i++) {
    buf.push(i);
  }
  ASSERT_EQ(buf.isEmpty(), false);

  for(int i = 0; i < 10; i++) {
    buf.pop();
  }
  ASSERT_EQ(buf.isEmpty(), true);

  RingBuffer<int, 1> singleItemBuf;
  ASSERT_EQ(singleItemBuf.isFull(), false);
  singleItemBuf.push(0);
  ASSERT_EQ(singleItemBuf.isFull(), true);
  singleItemBuf.pop();
  ASSERT_EQ(singleItemBuf.isFull(), false);
}

TEST(RingBuffer, isFull) {
  RingBuffer<int, 10> buf;

  ASSERT_EQ(buf.isFull(), false);
  buf.push(0);
  ASSERT_EQ(buf.isFull(), false);

  for(int i = 1; i < 10; i++) {
    buf.push(i);
  }
  ASSERT_EQ(buf.isFull(), true);

  buf.pop();
  for(int i = 1; i < 10; i++) {
    ASSERT_EQ(buf.isFull(), false);
    buf.pop();
  }

  ASSERT_EQ(buf.isFull(), false);
}
