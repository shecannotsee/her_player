/**
 * @file spdlog_wrapper.h
 * @brief Logging utility wrapper for `spdlog` with support for both production and test logging.
 *
 * This header provides a wrapper around the `spdlog` logging library, facilitating the creation of
 * daily and rotating log files, as well as console outputs. It distinguishes between regular
 * production logging and special test logging, each with its own configuration and logging levels.
 *
 * @author shecannotsee
 * @date 2024-10-23
 */
#ifndef HER_PLAYER_EXTERNAL_SPDLOG_WRAPPER_H
#define HER_PLAYER_EXTERNAL_SPDLOG_WRAPPER_H

#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>

#include <memory>

/**
 * @class spdlog_wrapper
 * @brief Provides static methods to manage logging with `spdlog`.
 *
 * The `spdlog_wrapper` class offers static utility methods to obtain a logger instance, manage log levels,
 * and configure logging outputs for both production and test scenarios. The class supports both
 * rotating log files and console output, using `spdlog`.
 */
class spdlog_wrapper {
 public:
  /**
   * @brief Deleted default constructor to prevent instantiation.
   */
  spdlog_wrapper() = delete;

  /** @brief The log file path for production logs. */
  static std::string log_file;

  /** @brief The log file path for test logs. */
  static std::string test_log_file;

  /** @brief The module name used for test logging. */
  static std::string test_module_name;

  /**
   * @brief Retrieves a logger instance.
   *
   * If the given name matches the test module name, a logger configured for testing is returned.
   * Otherwise, a regular production logger is created.
   *
   * @param name The name of the logger.
   * @return A shared pointer to the requested logger.
   */
  static auto get_logger(const std::string& name) -> std::shared_ptr<spdlog::logger>;

  /**
   * @brief Logs messages to the console at the specified log level.
   *
   * This template method logs messages at various log levels such as info, warn, error, debug,
   * and critical, using `spdlog`. The log level is specified via the `level` template parameter.
   *
   * @tparam level The logging level from `spdlog::level::level_enum`.
   * @tparam Args The argument types for the message to be logged.
   * @param args The arguments for the log message.
   */
  template <spdlog::level::level_enum level, typename... Args>
  static void console(Args&&... args);

 private:
  /** @brief Constant for megabytes, used in log file size calculations. */
  static constexpr int MB = 1024 * 1024;

  /**
   * @brief Creates or retrieves a rotating file logger.
   *
   * This method creates a rotating logger that writes to `log_file`. The log file size is limited
   * to 5 MB with up to 3 backup files maintained.
   *
   * @param name The name of the logger.
   * @return A shared pointer to the logger.
   */
  static auto create_logger(const std::string& name) -> std::shared_ptr<spdlog::logger>;

  /**
   * @brief Creates or retrieves a logger specifically for test logging.
   *
   * This logger is configured to write logs both to the console and to a rotating log file
   * (`test_log_file`) of up to 1 MB with 2 backup files maintained. The log level for this logger
   * is set to `trace` to capture detailed logs.
   *
   * @param name The name of the logger, defaults to `test_module_name`.
   * @return A shared pointer to the test logger.
   */
  static auto create_test_logger(const std::string& name = test_module_name) -> std::shared_ptr<spdlog::logger>;
};

#include "spdlog_wrapper_impl.h"

#endif  // HER_PLAYER_EXTERNAL_SPDLOG_WRAPPER_H
