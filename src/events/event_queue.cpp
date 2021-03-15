#include "lf/events/event_queue.hpp"
#include "lf/util/log.hpp"

namespace lf {

    EventQueue event_queue;

    EventQueue::EventQueue() {
    }

    EventQueue::~EventQueue() {
    }

    bool EventQueue::pushEvent(const Event& event) {
        if(!buffer.push(event)) {
          log::error("Failed to push event!");
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
      log::info("EventQueue: Listener added for EventType::{}", eventTypeName[static_cast<size_t>(eventType)]);
      callbackSets[static_cast<size_t>(eventType)].push_back(listener);
      return true;
    }
}