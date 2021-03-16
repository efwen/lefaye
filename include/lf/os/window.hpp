#pragma once
#include <cstdint>

#ifdef LF_WIN32
  #include <windows.h>
#endif

namespace lf::os {
  struct WindowProperties {
    std::string title;
    uint32_t x, y;
    uint32_t width, height;
  };

  class Window {
  public:
    Window();
    virtual ~Window();

    bool create(std::string_view title, uint32_t width, uint32_t height);
    bool destroy();
    bool update();

    void resize(uint32_t width, uint32_t height);
    bool isOpen();
  protected:
    HWND handle = NULL;
    WindowProperties props;
  };

  inline bool Window::isOpen() {
    return handle != NULL;
  };
}
