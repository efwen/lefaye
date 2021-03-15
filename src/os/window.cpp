#include "lf/pch.hpp"
#include "lf/os/window.hpp"
#include "fmt/core.h"
#include "lf/util/log.hpp"
#include "lf/events/event_queue.hpp"

namespace lf::os {

  LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
      case WM_CLOSE:  //does not work, need to have the actual hwnd
      {
        Event event;
        event.type = EventType::kWindowClose;
        
        event_queue.pushEvent(event);
        return 0;
      }
      case WM_SIZE:
      {
        Event event;
        event.type = EventType::kWindowResize;

        RECT rect;
        GetClientRect(hwnd, &rect);
        event.size_x = rect.right - rect.left;
        event.size_y = rect.bottom - rect.top;

        event_queue.pushEvent(event);
        break;
      }
      
      //Input Events
      case WM_KEYDOWN:
      {
        Event event;
        event.type = EventType::kKeyPressed;
        event.key_code = wParam;

        event_queue.pushEvent(event);
        break;
      }
      case WM_KEYUP:
      {
        Event event;
        event.type = EventType::kKeyReleased;
        event.key_code = wParam;

        event_queue.pushEvent(event);
        break;
      }

      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
      case WM_MBUTTONDOWN:
      {
        Event event;
        event.type = EventType::kMouseButtonPressed;

        if(message == WM_LBUTTONDOWN)
          event.button = MouseButton::kLeft;
        if(message == WM_RBUTTONDOWN)
          event.button = MouseButton::kRight;
        if(message == WM_MBUTTONDOWN)
          event.button = MouseButton::kMiddle;

        event.mouse_x = GET_X_LPARAM(lParam);
        event.mouse_y = GET_Y_LPARAM(lParam);

        event_queue.pushEvent(event);
        break;
      }

      case WM_LBUTTONUP:
      case WM_RBUTTONUP:
      case WM_MBUTTONUP:
      {
        Event event;
        event.type = EventType::kMouseButtonReleased;

        if(message == WM_LBUTTONUP)
        event.button = MouseButton::kLeft;
        if(message == WM_RBUTTONUP)
        event.button = MouseButton::kRight;
        if(message == WM_MBUTTONUP)
        event.button = MouseButton::kMiddle;

        event.mouse_x = GET_X_LPARAM(lParam);
        event.mouse_y = GET_Y_LPARAM(lParam);

        event_queue.pushEvent(event);
        break;
      }
      
      case WM_MOUSEMOVE:
      {
        Event event;
        event.type = EventType::kMouseMoved;
        event.mouse_x = GET_X_LPARAM(lParam);
        event.mouse_y = GET_Y_LPARAM(lParam);

        event_queue.pushEvent(event);
        break;
      }
      case WM_MOUSEWHEEL:
      {
        Event event;
        event.type = EventType::kMouseScroll;
        event.scroll_delta = GET_WHEEL_DELTA_WPARAM(wParam);

        event_queue.pushEvent(event);
        break;
      }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
  }

  Window::Window() :
    handle(NULL),
    props{0, 0, 0, 0}
    {}

  Window::~Window() {
    if(isOpen()) {
      destroy();
    }
  }

  bool Window::create(const char* title, uint32_t width, uint32_t height) {
    log::info("Creating Window. Title: \"{}\", Window Resolution: {}x{}",
        title, width, height);
    if(isOpen()) {
      log::error("Cannot create window. Already created!");
      return false;
    }


    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "LFWindowClass";

    RegisterClassEx(&wc);

    DWORD dwStyle = WS_OVERLAPPEDWINDOW;
    RECT wr = {0, 0, (long)width, (long)height};

    AdjustWindowRect(&wr, dwStyle, false);

    handle = CreateWindowEx(
        0,
        "LFWindowClass",
        title,
        dwStyle,
        300,
        300,
        wr.right - wr.left,
        wr.bottom - wr.top,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
      );

    if(handle == NULL) {
      log::error("Failed to open window! GetLastError() = {}", GetLastError());
      return false;
    }

    props = {title, 300, 300, width, height};

    ShowWindow(handle, SW_SHOW);

    return true;
  }

  bool Window::update() {
    if(handle == NULL) {
      log::error("Unable to update window. No window is open!");
      return false;
    }

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

  bool Window::destroy(){
    if(handle == NULL) {
      log::error("Unable to destroy window. No window is open!");
      return false;
    }

    DestroyWindow(handle);
    handle = NULL;
    return true;
  }

  void Window::resize(uint32_t width, uint32_t height) {
    //get the full size of the window, including borders etc.
    //because MoveWindow, etc. take the whole window size
    RECT wr = {0, 0, (long)width, (long)height};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);

    MoveWindow(handle, props.x, props.y,
        wr.right - wr.left,
        wr.bottom - wr.top,
        false);

    props.width = width;
    props.height = height;
  }
}
