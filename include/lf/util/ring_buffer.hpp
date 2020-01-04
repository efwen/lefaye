#pragma once

#include <array>

namespace lf::util {

  template<typename T, size_t buf_capacity>
  class RingBuffer {
    std::array<T, buf_capacity> buf;
    size_t buf_head;
    size_t buf_tail;
    size_t count;

  public:
    RingBuffer() :
      buf_head(0),
      buf_tail(0),
      count(0) {
        static_assert(buf_capacity > 0, "RingBuffer must have size of at least 1");
      };

    virtual ~RingBuffer() {
    };

    inline bool push(const T& item) {
      if(isFull()) {
        return false;
      }

      if(!isEmpty()) {
        buf_tail = (buf_tail + 1) % buf_capacity;
      }

      buf[buf_tail] = item;
      count++;

      return true;
    };

    inline bool pop(T& item) {
      T hold = buf[buf_head];

      if(pop()) {
        item = hold;
        return true;
      }

      return false;
    };

    inline bool pop() {
      if(isEmpty()) {
        return false;
      }

      if(count > 1) {
        buf_head = (buf_head + 1) % buf_capacity;
      }
      count--;

      return true;
    }

    inline bool peek(T& item) const {
      if(isEmpty()) {
        return false;
      }

      item = buf[buf_head];
      return true;
    };

    inline size_t getCapacity() const {
      return buf_capacity;
    }

    inline size_t getSize() const {
      return count;
    }

    inline bool isEmpty() const {
      return count == 0;
    }

    inline bool isFull() const {
        return count == buf_capacity;
    }
  };

}
