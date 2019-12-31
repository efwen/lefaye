#pragma once

#include "lf/util/ring_buffer.hpp"

namespace os {

  enum EventType: uint32_t {
    kNone = 0,
    kWindowOpen,
    kWindowClose,
    kWindowMaximize,
    kWindowMinimize,
    kWindowKeyDown,
    kWindowKeyUp,
    kWindowMouseMove
  };

  struct OsEvent {
    EventType type;
  };

  class EventQueue {
    RingBuffer<OsEvent, 256> buf;
  public:
    EventQueue();
    virtual ~EventQueue();

    bool pushEvent(const OsEvent& event);
    bool addListener(OsEventListener listener);
    bool removeListener(OsEventListener listener);
  }
}
