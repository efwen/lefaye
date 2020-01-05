#pragma once

#include <array>
#include <string_view>

#include <fmt/format.h>

namespace lf::log {

  enum class Level : uint8_t {
    kInfo = 0,
    kWarn,
    kError,
  };

  enum class Color : uint8_t {
#ifdef LF_WIN32
    kBlack = 0,
    kBlue,
    kGreen,
    kCyan,
    kRed,
    kMagenta,
    kYellow,
    kWhite,
#else
    kBlack = 30,
    kRed,
    kGreen,
    kYellow,
    kBlue,
    kMagenta,
    kCyan,
    kWhite,
#endif
  };

  constexpr std::array<const char*, 3> levelPrefixes = {
    "[INFO]:  ",
    "[WARN]:  ",
    "[ERROR]: "
  };

  constexpr std::array<log::Color, 3> levelColors = {
    log::Color::kCyan,
    log::Color::kYellow,
    log::Color::kRed
  };

  void init();

  void vLogMessage(log::Level severity, std::string_view format, fmt::format_args args);

  template<typename... Args>
  void info(std::string_view format, const Args&... args) {
    vLogMessage(log::Level::kInfo, format, fmt::make_format_args(args...));
  }

  template <typename... Args>
  void warn(std::string_view format, const Args&... args) {
    vLogMessage(log::Level::kWarn, format, fmt::make_format_args(args...));
  }

  template<typename... Args>
  void error(std::string_view format, const Args&... args) {
    vLogMessage(log::Level::kError, format, fmt::make_format_args(args...));
  }
}

