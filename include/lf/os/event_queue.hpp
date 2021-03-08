#pragma once

#include "lf/util/ring_buffer.hpp"
#include <array>
#include <vector>

namespace lf::os {

  constexpr unsigned int kOsEventBufferSize = 256;

  enum EventType: uint32_t {
    kNone = 0,
    kShutdown,
    kWindowClose,
    kWindowResize,
    kKeyPressed,
    kKeyReleased,
    kMouseMove,
    kMouseButtonPressed,
    kMouseButtonReleased,
    kMouseScroll,
    kSize
  };

  enum MouseButton: uint16_t {
    kLeft = 0,
    kRight,
    kMiddle
  };

  struct Event {
    EventType     type;
    uint16_t      key_code;
    int16_t       mouse_x;
    int16_t       mouse_y;
    MouseButton   button;
    int32_t       scroll_delta;
    uint16_t      size_x;
    uint16_t      size_y;
  };

  using OsEventListener = void (*)(Event&);

  class OsEventQueue {
    util::RingBuffer<Event, kOsEventBufferSize> buffer;
    typedef std::vector<OsEventListener> OsEventListenerSet;
    std::array<OsEventListenerSet, EventType::kSize> listenerSets;
  public:
    OsEventQueue();
    virtual ~OsEventQueue();

    bool pushEvent(const Event& event);
    void processEvents();
    bool addListener(EventType eventType, OsEventListener listener);
  };

  extern OsEventQueue event_queue;
}
