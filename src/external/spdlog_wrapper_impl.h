#ifndef HER_PLAYER_EXTERNAL_SPDLOG_WRAPPER_IMPL_H
#define HER_PLAYER_EXTERNAL_SPDLOG_WRAPPER_IMPL_H

#include "spdlog_wrapper.h"

template <spdlog::level::level_enum level, typename... Args>
void spdlog_wrapper::console(Args&&... args) {
  using namespace spdlog::level;
  if constexpr (level == info) {
    spdlog::info(std::forward<Args>(args)...);
  } else if constexpr (level == warn) {
    spdlog::warn(std::forward<Args>(args)...);
  } else if constexpr (level == err) {
    spdlog::error(std::forward<Args>(args)...);
  } else if constexpr (level == debug) {
    spdlog::debug(std::forward<Args>(args)...);
  } else if constexpr (level == critical) {
    spdlog::critical(std::forward<Args>(args)...);
  }
}

#endif  // HER_PLAYER_EXTERNAL_SPDLOG_WRAPPER_IMPL_H
