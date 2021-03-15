#pragma once

#include "lf/util/ring_buffer.hpp"
#include <array>
#include <vector>
#include <functional>

namespace lf {

  constexpr uint16_t kEventBufferSize = 4096;

  enum class EventType : uint8_t {
    kShutdown = 0,
    kWindowClose,
    kWindowResize,
    kKeyPressed,
    kKeyReleased,
    kMouseMoved,
    kMouseButtonPressed,
    kMouseButtonReleased,
    kMouseScroll,
    kSize
  };

  constexpr std::array<const char*, static_cast<size_t>(EventType::kSize)> eventTypeName {
    "kShutdown",
    "kWindowClose",
    "kWindowResize",
    "kKeyPressed",
    "kKeyReleased",
    "kMouseMoved",
    "kMouseButtonPressed",
    "kMouseButtonReleased",
    "kMouseScroll"
  };

  enum class MouseButton: uint8_t {
    kLeft = 0,
    kRight,
    kMiddle,
    kSize
  };

  constexpr std::array<const char*, static_cast<size_t>(MouseButton::kSize)> mouseButtonName {
    "kLeft",
    "kRight",
    "kMiddle"
  };

  struct Event {
    EventType     type;
    uint16_t      key_code;
    int16_t       mouse_x;
    int16_t       mouse_y;
    MouseButton   button;
    int16_t       scroll_delta;
    uint16_t      size_x;
    uint16_t      size_y;
  };

  using EventCallback = std::function<void(const Event& e)>;
  typedef std::vector<EventCallback> EventCallbackSet;

  class EventQueue {
    util::RingBuffer<Event, kEventBufferSize> buffer;
    std::array<EventCallbackSet, static_cast<size_t>(EventType::kSize)> callbackSets;
  public:
    virtual ~EventQueue() = default;

    bool pushEvent(const Event& event);
    void dispatchEvents();
    bool addCallback(EventType eventType, EventCallback callback);
  };

  extern EventQueue event_queue;
}
