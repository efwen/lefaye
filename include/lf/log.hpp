#pragma once

#include <array>
#include <string_view>

#ifdef LF_WIN32
  #include <Windows.h>
#endif

#include <fmt/format.h>

namespace lf::log {

  enum class Level {
    kInfo = 0,
    kWarn,
    kError
  };

  enum class Color {
    kDefault = 0,
    kBlue = 36,
    kYellow = 33,
    kRed = 31,
  };

  namespace internal {
    constexpr std::array<const char*, 3> prefixStrings = {
      "[INFO]:  ",
      "[WARN]:  ",
      "[ERROR]: "
    };

#ifdef LF_WIN32
    HANDLE consoleHandle;
#endif

    inline void setColor(log::Color color) {
#ifdef LF_WIN32
      SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE);
#else
      fmt::print("\033[0;{}m", static_cast<uint32_t> color);
#endif
    }

    inline void vLogMessage(log::Level severity, std::string_view format, fmt::format_args args) {
      setColor(log::Color::kRed);
      fmt::vprint(
        fmt::format("{} {}\n",
          prefixStrings[static_cast<uint32_t>(severity)],
          format),
        args);
      fmt::print("{}\n", FOREGROUND_RED);
      fmt::print("{}\n", FOREGROUND_BLUE);
      fmt::print("{}\n", FOREGROUND_GREEN);
      fmt::print("{}\n", FOREGROUND_INTENSITY);
      setColor(log::Color::kDefault);
    }
  }
 
  inline void init() {
#ifdef LF_WIN32
    internal::consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
  }

  template<typename... Args>
  void info(std::string_view format, const Args&... args) {
    internal::vLogMessage(log::Level::kInfo, format, fmt::make_format_args(args...));
  }

  template <typename... Args>
  void warn(std::string_view format, const Args&... args) {
    internal::vLogMessage(log::Level::kWarn, format, fmt::make_format_args(args...));
  }

  template<typename... Args>
  void error(std::string_view format, const Args&... args) {
    internal::vLogMessage(log::Level::kError, format, fmt::make_format_args(args...));
  }
}

