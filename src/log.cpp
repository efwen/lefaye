#include "lf/pch.hpp"
#include "lf/log.hpp"

namespace lf::log {

#ifdef LF_WIN32
  HANDLE consoleHandle = INVALID_HANDLE_VALUE;
#endif

  void setColor(log::Color color) {
#ifdef LF_WIN32
    SetConsoleTextAttribute(consoleHandle, static_cast<uint32_t>(color));
#else
    fmt::print("\033[0;{}m", static_cast<uint32_t> color);
#endif
  }

  void vLogMessage(log::Level severity, std::string_view format, fmt::format_args args) {
    setColor(levelColors[static_cast<uint8_t>(severity)]);
    fmt::vprint(
      fmt::format("{} {}\n",
        levelPrefixes[static_cast<uint32_t>(severity)],
        format),
      args);
    setColor(log::Color::kWhite);
  }

  void init() {
#ifdef LF_WIN32
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
  }
}
