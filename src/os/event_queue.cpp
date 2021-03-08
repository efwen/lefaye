#include "lf/os/event_queue.hpp"
#include "lf/util/log.hpp"

namespace lf::os {

    OsEventQueue event_queue;

    OsEventQueue::OsEventQueue() {
    }

    OsEventQueue::~OsEventQueue() {
    }

    bool OsEventQueue::pushEvent(const Event& event) {
        if(!buffer.push(event)) {
          log::error("Failed to push event!");
          return false;
        }
        return true;
    }

    void OsEventQueue::processEvents() {
      Event event;
      while(buffer.pop(event)) {
        for(OsEventListener listener : listenerSets[static_cast<size_t>(event.type)]) {
          listener(event);
        }
      }
    }

    bool OsEventQueue::addListener(EventType eventType, OsEventListener listener) {
      listenerSets[static_cast<size_t>(eventType)].push_back(listener);
      return true;
    }
}
