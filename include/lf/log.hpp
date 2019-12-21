#pragma once
#include <array>
#include <string_view>

#include <fmt/format.h>

namespace lf::log {

  enum class Level {
    kInfo = 0,
    kWarn,
    kError
  };

  namespace internal {
    constexpr std::array<const char*, 3> levelFmtStrings = {
      "\033[0;36m[INFO]:  {}\033[0;0m\n", //blue text
      "\033[0;33m[WARN]:  {}\033[0;0m\n", //yellow text
      "\033[0;31m[ERROR]: {}\033[0;0m\n"  //red text
    };

    inline void vLogMessage(log::Level severity, std::string_view format, fmt::format_args args) {
      fmt::vprint(
          fmt::format(internal::levelFmtStrings[static_cast<size_t>(severity)], format),
          args);
    }
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

