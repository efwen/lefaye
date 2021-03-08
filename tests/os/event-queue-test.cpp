#include <gtest/gtest.h>
#include <lf/os/event_queue.hpp>

using namespace lf::os;

TEST(EventQueue, ShutdownEvent) {
  EventType type = EventType::kShutdown;
  bool wasCalled = false;

  event_queue.addListener(type, [&wasCalled](Event& e) {
    wasCalled = true;
  });

  Event event;
  event.type = type;
  event_queue.pushEvent(event);

  event_queue.processEvents();

  ASSERT_EQ(wasCalled, true); 
}

TEST(EventQueue, WindowCloseEvent) {
  EventType type = EventType::kWindowClose;
  bool wasCalled = false;

  event_queue.addListener(type, [&wasCalled](Event& e) {
    wasCalled = true;
  });

  Event event;
  event.type = type;
  event_queue.pushEvent(event);

  event_queue.processEvents();

  ASSERT_EQ(wasCalled, true); 
}

TEST(EventQueue, WindowResizeEvent) {
  EventType type = EventType::kWindowResize;
  bool wasCalled = false;
  uint32_t size_x = 0;
  uint32_t size_y = 0;
  
  event_queue.addListener(type, [&wasCalled, &size_x, &size_y](Event& e) {
    wasCalled = true;
    size_x = e.size_x;
    size_y = e.size_y;
  });

  Event event;
  event.type = type;
  event.size_x = 400;
  event.size_y = 520;
  event_queue.pushEvent(event);

  event_queue.processEvents();

  ASSERT_EQ(wasCalled, true); 
  ASSERT_EQ(event.size_x, size_x);
  ASSERT_EQ(event.size_y, size_y);
}

TEST(EventQueue, KeyPressedEvent) {
  EventType type = EventType::kKeyPressed;
  bool wasCalled = false;
  uint16_t key_code = 0;

  event_queue.addListener(type, [&wasCalled, &key_code](Event& e) {
    wasCalled = true;
    key_code = e.key_code;
  });

  Event event;
  event.type = type;
  event.key_code = 42;
  event_queue.pushEvent(event);

  event_queue.processEvents();

  ASSERT_EQ(wasCalled, true); 
  ASSERT_EQ(event.key_code, key_code);
}

TEST(EventQueue, KeyReleasedEvent) {
  EventType type = EventType::kKeyReleased;
  bool wasCalled = false;
  uint16_t key_code = 0;

  event_queue.addListener(type, [&wasCalled, &key_code](Event& e) {
    wasCalled = true;
    key_code = e.key_code;
  });

  Event event;
  event.type = type;
  event.key_code = 42;
  event_queue.pushEvent(event);

  event_queue.processEvents();

  ASSERT_EQ(wasCalled, true); 
  ASSERT_EQ(event.key_code, key_code);
}

TEST(EventQueue, MouseMovedEvent) {
  EventType type = EventType::kMouseMoved;
  bool wasCalled = false;
  uint16_t mouse_x = 0;
  uint16_t mouse_y = 0;

  event_queue.addListener(type, [&wasCalled, &mouse_x, &mouse_y](Event& e) {
    wasCalled = true;
    mouse_x = e.mouse_x;
    mouse_y = e.mouse_y;
  });

  Event event;
  event.type = type;
  event.mouse_x = 430;
  event.mouse_y = 233;
  event_queue.pushEvent(event);

  event_queue.processEvents();

  ASSERT_EQ(wasCalled, true); 
  ASSERT_EQ(event.mouse_x, mouse_x);
  ASSERT_EQ(event.mouse_y, mouse_y);
}

TEST(EventQueue, MouseButtonPressedEvent) {
  EventType type = EventType::kMouseButtonPressed;
  bool wasCalled = false;
  MouseButton button = MouseButton::kSize;

  event_queue.addListener(type, [&wasCalled, &button](Event& e) {
    wasCalled = true;
    button = e.button;
  });

  Event event;
  event.type = type;
  event.button = MouseButton::kLeft;
  event_queue.pushEvent(event);

  event_queue.processEvents();

  ASSERT_EQ(wasCalled, true); 
  ASSERT_EQ(event.button, button);
}

TEST(EventQueue, MouseButtonReleasedEvent) {
  EventType type = EventType::kMouseButtonReleased;
  bool wasCalled = false;
  MouseButton button = MouseButton::kSize;

  event_queue.addListener(type, [&wasCalled, &button](Event& e) {
    wasCalled = true;
    button = e.button;
  });

  Event event;
  event.type = type;
  event.button = MouseButton::kLeft;
  event_queue.pushEvent(event);

  event_queue.processEvents();

  ASSERT_EQ(wasCalled, true); 
  ASSERT_EQ(event.button, button);
}

TEST(EventQueue, MouseScrollEvent) {
  EventType type = EventType::kMouseScroll;
  bool wasCalled = false;
  int16_t delta = 0;

  event_queue.addListener(type, [&wasCalled, &delta](Event& e) {
    wasCalled = true;
    delta = e.scroll_delta;
  });

  Event event;
  event.type = type;
  event.scroll_delta = 120;
  event_queue.pushEvent(event);

  event_queue.processEvents();

  ASSERT_EQ(wasCalled, true); 
  ASSERT_EQ(event.scroll_delta, delta);
}