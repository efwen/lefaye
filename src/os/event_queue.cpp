#include "lf/os/event_queue.hpp"
#include "lf/util/log.hpp"

namespace lf::os {

    OsEventQueue g_event_queue;

    OsEventQueue::OsEventQueue() {
    }

    OsEventQueue::~OsEventQueue() {
    }

    bool OsEventQueue::pushEvent(const OsEvent& event) {
        if(!buffer.push(event)) {
          log::error("Failed to push event!");
          return false;
        }

        log::info("Event pushed");
        return true;
    }

    void OsEventQueue::processEvents() {
      while(!buffer.isEmpty()) {
        OsEvent event;
        buffer.pop(event);
        log::info("Event Processed: {}", event.e_type);
      }
    }

    bool OsEventQueue::addListener(const OsEventListener& listener) {
    }

    bool OsEventQueue::removeListener(const OsEventListener& listener) {
    }
}
