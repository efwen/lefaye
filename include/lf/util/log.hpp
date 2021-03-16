#pragma once

#include <array>
#include <string_view>

#include <fmt/format.h>

namespace lf::log {

  enum class Level : uint8_t {
    kTrace = 0,
    kInfo,
    kWarn,
    kError,
    kSize,
  };

  enum class Color : uint16_t {
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

  constexpr std::array<const char*, static_cast<size_t>(Level::kSize)> levelPrefixes = {
    "[TRACE]: ",
    "[INFO]:  ",
    "[WARN]:  ",
    "[ERROR]: "
  };

  constexpr std::array<log::Color, static_cast<size_t>(Level::kSize)> levelColors = {
    log::Color::kWhite,
    log::Color::kCyan,
    log::Color::kYellow,
    log::Color::kRed
  };

  void init(std::string_view short_app_title);

  void vLogLefayeMessage(log::Level severity, std::string_view format, fmt::format_args args);
  void vLogClientMessage(log::Level severity, std::string_view format, fmt::format_args args);

  template <typename... Args>
  void trace(std::string_view format, const Args&... args) {
    vLogClientMessage(log::Level::kTrace, format, fmt::make_format_args(args...));
  }

  template<typename... Args>
  void info(std::string_view format, const Args&... args) {
    vLogClientMessage(log::Level::kInfo, format, fmt::make_format_args(args...));
  }

  template <typename... Args>
  void warn(std::string_view format, const Args&... args) {
    vLogClientMessage(log::Level::kWarn, format, fmt::make_format_args(args...));
  }

  template<typename... Args>
  void error(std::string_view format, const Args&... args) {
    vLogClientMessage(log::Level::kError, format, fmt::make_format_args(args...));
  }
}