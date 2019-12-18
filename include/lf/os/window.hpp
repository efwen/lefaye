#pragma once
#include <cstdint>

#ifdef LF_WIN32
  #include <windows.h>
#endif

namespace lf::os {
  class Window {
  public:
    Window();
    virtual ~Window();

    bool create(const char* title, uint32_t width, uint32_t height);
    void destroy();
    bool update();
  protected:
    HWND handle = NULL;
  };
}
