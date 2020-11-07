#ifndef ENGINE_COMMON_EXCEPTIONS_H
#define ENGINE_COMMON_EXCEPTIONS_H

#include <stdexcept>
#include <string>

/**
 * @brief Exception raised when a file is not found
 *
 */
class FileIOException : public std::runtime_error {
 public:
  explicit FileIOException(const std::string& msg) : std::runtime_error(msg) {}
};

/**
 * @brief Exception raised when a core feature can not load
 *
 */
class InitException : public std::runtime_error {
 public:
  explicit InitException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif  // ENGINE_COMMON_EXCEPTIONS_H
