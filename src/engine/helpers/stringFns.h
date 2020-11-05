#include <memory>
#include <stdexcept>
#include <string>

namespace stringFns {

// Checks
extern bool isInteger(std::string str);
extern bool isBoolean(std::string str);
extern bool isFloat(std::string str);

// Conversions
extern int toInteger(std::string str);
extern bool toBoolean(std::string str);
extern float toFloat(std::string str);

template <typename... Args>
std::string format(const std::string& format, Args... args) {
  int size = snprintf(nullptr, 0, format.c_str(), args...) + 1;
  if (size <= 0) {
    throw std::runtime_error("Error during formatting.");
  }
  std::unique_ptr<char[]> buf(new char[size]);
  snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(), buf.get() + size - 1);
}

}  // namespace stringFns