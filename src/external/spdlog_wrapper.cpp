#include "spdlog_wrapper.h"

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>

/** @brief Default log file path for production logging. */
std::string spdlog_wrapper::log_file = "her_player.log";

/** @brief Default log file path for test logging. */
std::string spdlog_wrapper::test_log_file = "her_player_test.log";

/** @brief Default module name used for test logging. */
std::string spdlog_wrapper::test_module_name = "test";

auto spdlog_wrapper::get_logger(const std::string& name) -> std::shared_ptr<spdlog::logger> {
  if (name == test_module_name) {
    static const std::shared_ptr<spdlog::logger> INSTANCE = create_test_logger();
    return INSTANCE;
  }
  return create_logger(name);
}

auto spdlog_wrapper::create_logger(const std::string& name) -> std::shared_ptr<spdlog::logger> {
  auto logger = spdlog::get(name);
  if (!logger) {
    logger = spdlog::rotating_logger_mt(name, log_file, 5 * MB, 3);
  }
  return logger;
}

auto spdlog_wrapper::create_test_logger(const std::string& name) -> std::shared_ptr<spdlog::logger> {
  std::vector<spdlog::sink_ptr> sinks;
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
  sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_st>(test_log_file, 1 * MB, 2));
  auto combined_logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
  register_logger(combined_logger);
  combined_logger->set_level(spdlog::level::trace);
  return combined_logger;
}
