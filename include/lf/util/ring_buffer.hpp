#pragma once

#include <array>

namespace lf::util {

  template<typename T, size_t buf_capacity>
  class RingBuffer {
    std::array<T, buf_capacity> buf;
    size_t buf_head;
    size_t buf_tail;

  public:
    RingBuffer() :
      buf_head(0),
      buf_tail(0)
      {};

    virtual ~RingBuffer() {
    };

    inline bool push(const T& item) {
        assert(getSize() < buf_capacity)

        if(!isEmpty())
          buf_head = (buf_head + 1) % buf_capacity;

        buf[buf_head] = item;
    };

    inline T pop() {
      assert(!isEmpty());

      T item = buf[buf_tail];
      buf_tail = (buf_tail + buf_capacity + 1) % buf_capacity;

      return item;
    };

    inline T peek() const {
        assert(!isEmpty());

        return buf[buf_tail];
    };

    inline size_t getCapacity() const {
      return buf_capacity;
    }

    inline size_t getSize() const {
      return (buf_capacity + buf_head - buf_tail) % buf_capacity;
    }

    inline bool isEmpty() const {
      return buf_head == buf_tail;
    }
  };

}
