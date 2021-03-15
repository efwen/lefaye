#include "lf/util/log.hpp"

//logging methods only accessible to the engine itself
namespace lf::log::internal {
  template <typename... Args>
  void trace(std::string_view format, const Args&... args) {
    vLogLefayeMessage(log::Level::kTrace, format, fmt::make_format_args(args...));
  }

  template<typename... Args>
  void info(std::string_view format, const Args&... args) {
    vLogLefayeMessage(log::Level::kInfo, format, fmt::make_format_args(args...));
  }

  template <typename... Args>
  void warn(std::string_view format, const Args&... args) {
    vLogLefayeMessage(log::Level::kWarn, format, fmt::make_format_args(args...));
  }

  template<typename... Args>
  void error(std::string_view format, const Args&... args) {
    vLogLefayeMessage(log::Level::kError, format, fmt::make_format_args(args...));
  }
}