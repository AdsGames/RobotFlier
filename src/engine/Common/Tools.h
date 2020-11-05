/**
 * TOOLS
 * Allan Legemaate
 * General purpose utilities used throughout
 * 05/05/2017
 **/

#ifndef ENGINE_COMMON_TOOLS_H
#define ENGINE_COMMON_TOOLS_H

#include <sstream>
#include <string>
#include <vector>

#include <allegro5/allegro_font.h>

// Tools class
class tools {
 public:
  // Convert char to float
  static void abort_on_error(const std::string& message,
                             const std::string& title);

  static bool file_exists(const std::string& filePath);

  // Clamp values
  template <class T>
  static T clamp(T min_val, T max_val, T value) {
    if (value < min_val)
      return min_val;

    if (value > max_val)
      return max_val;

    return value;
  }

  // Clamp values
  template <class T>
  static T negative_clamp_thing(T min_val, T max_val, T value) {
    if (value < min_val)
      return min_val + -1 * value;

    if (value > max_val)
      return max_val - value;

    return value;
  }

  // Function to check for collision
  template <class T>
  static bool collision(T xMin1,
                        T xMax1,
                        T xMin2,
                        T xMax2,
                        T yMin1,
                        T yMax1,
                        T yMin2,
                        T yMax2) {
    return xMin1 < xMax2 && yMin1 < yMax2 && xMin2 < xMax1 && yMin2 < yMax1;
  }

  // Debug message
  static void log_message(const std::string& message, const bool debug = false);
};

#endif  // ENGINE_COMMON_TOOLS_H
