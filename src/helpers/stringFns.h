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

}  // namespace stringFns