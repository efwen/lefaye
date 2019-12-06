#include "lf/lefaye.hpp"

#include <cstdio>
#include <vulkan/vulkan.h>
#include <windows.h>

namespace lf {

  HWND handle = NULL;

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

  void init(uint32_t width, uint32_t height) { 
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "LFWindowClass";

    RegisterClassEx(&wc);

    HWND handle = CreateWindowEx(
        0,
        "LFWindowClass",
        "LeFaye",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
        );

    ShowWindow(handle, SW_SHOW);
  }

  void shutdown() {
    DestroyWindow(handle);
  }

  bool updateWindow() {
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

  uint32_t getVulkanExtensionCount() {
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    return extensionCount;
  }

  int add_vals(int a, int b) {
    return a + b;
  }
}
