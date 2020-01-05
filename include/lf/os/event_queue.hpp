#pragma once

#include "lf/util/ring_buffer.hpp"
#include <functional>

namespace lf::os {

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
    EventType e_type;
    uint32_t  e_data;
  };

  typedef std::function<void(const OsEvent&)> OsEventListener;

  class OsEventQueue {
    util::RingBuffer<OsEvent, 256> buffer;
  public:
    OsEventQueue();
    virtual ~OsEventQueue();

    bool pushEvent(const OsEvent& event);
    void processEvents();
    bool addListener(const OsEventListener& listener);
    bool removeListener(const OsEventListener& listener);
  };

  extern OsEventQueue g_event_queue;
}
