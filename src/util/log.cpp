#include "lf/pch.hpp"
#include "lf/util/log.hpp"

namespace lf::log {

  std::string app_prefix = "";
  constexpr auto lefaye_prefix = "[LeFaye]";

#ifdef LF_WIN32
  HANDLE consoleHandle = INVALID_HANDLE_VALUE;
#endif

  void setColor(log::Color color) {
#ifdef LF_WIN32
    SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(color));
#else
    fmt::print("\033[0;{}m", static_cast<uint8_t> color);
#endif
  }

  void vLogMessage(log::Level severity, std::string_view format, std::string_view source_prefix, fmt::format_args args) {
    setColor(levelColors[static_cast<size_t>(severity)]);
    fmt::vprint(
      fmt::format("{}{} {}\n",
        source_prefix,
        levelPrefixes[static_cast<size_t>(severity)],
        format),
      args);
    setColor(log::Color::kWhite);
  }

  void vLogLefayeMessage(log::Level severity, std::string_view format, fmt::format_args args) {
    vLogMessage(severity, format, lefaye_prefix, args);
  }

  void vLogClientMessage(log::Level severity, std::string_view format, fmt::format_args args) {
    vLogMessage(severity, format, app_prefix, args);
  }


  void init(std::string_view short_app_title) {
#ifdef LF_WIN32
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    app_prefix = fmt::format("[{}]", short_app_title);
  }
}
