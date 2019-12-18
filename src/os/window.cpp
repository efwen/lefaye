#include "lf/os/window.hpp"
#include "lf/log.hpp"

#include <cstdint>

#include <windows.h>

namespace lf::os {

  LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
      case WM_SIZE:
        return 0;
      case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
      case WM_CLOSE:
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
  }

  Window::Window() :
    handle(NULL)
    {}

  Window::~Window() {
    destroy();
  }

  bool Window::create(const char* title, uint32_t width, uint32_t height) {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "LFWindowClass";

    RegisterClassEx(&wc);

    handle = CreateWindowEx(
        0,
        "LFWindowClass",
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
        );

    if(handle == NULL) {
      log::error("Failed to open window!");
      return false;
    }

    ShowWindow(handle, SW_SHOW);

    return true;
  }

  bool Window::update() {
    MSG msg;
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if(msg.message == WM_QUIT) {
        return false;
      }

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    return true;
  }

  void Window::destroy(){
    PostQuitMessage(0);
  }
}
