#pragma once

#include "lf/util/ring_buffer.hpp"
#include <array>
#include <vector>
#include <functional>

namespace lf::os {

  constexpr uint16_t kOsEventBufferSize = 256;

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

  using OsEventListener = std::function<void(Event&)>;
  class OsEventQueue {
    util::RingBuffer<Event, kOsEventBufferSize> buffer;
    typedef std::vector<OsEventListener> OsEventListenerSet;
    std::array<OsEventListenerSet, static_cast<size_t>(EventType::kSize)> listenerSets;
  public:
    OsEventQueue();
    virtual ~OsEventQueue();

    bool pushEvent(const Event& event);
    void dispatchEvents();
    bool addListener(EventType eventType, OsEventListener listener);
  };

  extern OsEventQueue event_queue;
}
