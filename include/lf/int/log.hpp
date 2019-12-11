#pragma once

#include <fmt/format.h>

#include <array>
#include <string_view>

namespace lf::log {

  enum class Level {
    INFO = 0,
    WARN,
    ERROR
  };

  namespace internal {
    constexpr std::array<const char*, 3> levelFmtStrings = {
      "\033[0;36m[INFO]:  {}\n", //blue text
      "\033[0;33m[WARN]:  {}\n", //yellow text
      "\033[0;31m[ERROR]: {}\n"  //red text
    };

    inline void vLogMessage(log::Level severity, std::string_view format, fmt::format_args args) {
      fmt::vprint(
          fmt::format(internal::levelFmtStrings[static_cast<size_t>(severity)], format),
          args);
    }
  }

  template<typename... Args>
  void info(std::string_view format, const Args&... args) {
    internal::vLogMessage(log::Level::INFO, format, fmt::make_format_args(args...));
  }

  template <typename... Args>
  void warn(std::string_view format, const Args&... args) {
    internal::vLogMessage(log::Level::WARN, format, fmt::make_format_args(args...));
  }

  template<typename... Args>
  void error(std::string_view format, const Args&... args) {
    internal::vLogMessage(log::Level::ERROR, format, fmt::make_format_args(args...));
  }
}

