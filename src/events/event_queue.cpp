#include "lf/events/event_queue.hpp"
#include "lf/util/log.hpp"
#include "lf/util/log_internal.hpp"

namespace lf {

    EventQueue event_queue;

    bool EventQueue::pushEvent(const Event& event) {
        if(!buffer.push(event)) {
          log::internal::error("Failed to push event! Buffer is full!");
          return false;
        }
        
        return true;
    }

    void EventQueue::dispatchEvents() {
      Event event;
      while(buffer.pop(event)) {
        for(EventCallback callback : callbackSets[static_cast<size_t>(event.type)]) {
          callback(event);
        }
      }
    }

    bool EventQueue::addCallback(EventType eventType, EventCallback listener) {
      log::internal::info("EventQueue: Listener added for EventType::{}", eventTypeName[static_cast<size_t>(eventType)]);
      callbackSets[static_cast<size_t>(eventType)].push_back(listener);
      return true;
    }
}