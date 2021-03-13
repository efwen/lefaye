#pragma once

namespace lf {
  class App {
  public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;
  };
}