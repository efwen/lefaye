#pragma once

#include <string_view>

namespace lf {
  class App {
  public:
    struct BootProperties {
      std::string title;
      uint32_t window_width;
      uint32_t window_height;
    };

    App(const BootProperties& props) : 
      boot_props(props) {}
    virtual ~App() = default;
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;
    const BootProperties& getBootProps() { return boot_props; }
  private:
    BootProperties boot_props;
  };
}