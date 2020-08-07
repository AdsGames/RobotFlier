#include "Tools.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>

#include <fstream>
#include <iostream>

#include "../Input/MouseListener.h"

// A function to streamline error reporting in file loading
void tools::abort_on_error(std::string message, std::string title) {
  al_show_native_message_box(nullptr, "Error", title.c_str(), message.c_str(),
                             nullptr, ALLEGRO_MESSAGEBOX_ERROR);
  exit(-1);
}

// Check if file exists
bool tools::file_exists(std::string filePath) {
  std::ifstream file(filePath.c_str());
  return file.good();
}

// Text offset x
int tools::get_text_offset_x(ALLEGRO_FONT* newFont, std::string newText) {
  int text_width, text_height, text_offset_x, text_offset_y = 0;
  al_get_text_dimensions(newFont, newText.c_str(), &text_offset_x,
                         &text_offset_y, &text_width, &text_height);
  return text_offset_x;
}

// Text offset y
int tools::get_text_offset_y(ALLEGRO_FONT* newFont, std::string newText) {
  int text_width, text_height, text_offset_x, text_offset_y = 0;
  al_get_text_dimensions(newFont, newText.c_str(), &text_offset_x,
                         &text_offset_y, &text_width, &text_height);
  return text_offset_y;
}

// Text offset width
int tools::get_text_width(ALLEGRO_FONT* newFont, std::string newText) {
  int text_width, text_height, text_offset_x, text_offset_y = 0;
  al_get_text_dimensions(newFont, newText.c_str(), &text_offset_x,
                         &text_offset_y, &text_width, &text_height);
  return text_width;
}

// Text offset height
int tools::get_text_height(ALLEGRO_FONT* newFont, std::string newText) {
  int text_width, text_height, text_offset_x, text_offset_y = 0;
  al_get_text_dimensions(newFont, newText.c_str(), &text_offset_x,
                         &text_offset_y, &text_width, &text_height);
  return text_height;
}

// Convert string to int
int tools::stringToInt(std::string str) {
  if (str == "")
    return 0;

  int result;
  std::stringstream(str) >> result;
  return result;
}

// Convert char to float
float tools::stringToFloat(std::string str) {
  if (str == "")
    return 0.0f;

  float number = 0.0f;
  int sign = 1;

  // Parse string
  // Negative
  if (str[0] == '-') {
    sign = -1;
    str = str.substr(1, str.length());
  }

  // Location of decimal
  int decimal_loc = str.length();

  for (unsigned int i = 0; i < str.length(); i++) {
    if (str[i] == '.') {
      decimal_loc = i;
      str = str.substr(0, i) + str.substr(i + 1, str.length() - i);
    }
  }

  // Numbers
  for (unsigned int i = 0; i < str.length(); i++) {
    int tempNumber = int(str[i]) - 48;
    number += tempNumber * pow(10, (str.length()) - (i + 1));
  }

  return (number / float(pow(10, str.length() - decimal_loc))) * sign;
}

// Split string
std::vector<std::string> tools::split_string(const std::string& p_pcstStr,
                                             const char delim) {
  std::vector<std::string> tokens;
  std::stringstream mySstream(p_pcstStr);
  std::string temp;

  while (getline(mySstream, temp, delim))
    tokens.push_back(temp);

  return tokens;
}

// Random number
int tools::random_int(const int min, const int max) {
  return (rand() % (max + 1 - min)) + min;
}

// Log message to console
void tools::log_message(std::string message, bool debug) {
  if (debug) {
#ifdef Debug
    std::cout << message << "\n";
#endif
  } else {
    std::cout << message << "\n";
  }
}

// Mouse over
bool tools::mouse_over(const int x,
                       const int y,
                       const int width,
                       const int height) {
  return tools::collision(MouseListener::mouse_x, MouseListener::mouse_x, x,
                          x + width, MouseListener::mouse_y,
                          MouseListener::mouse_y, y, y + height);
}

// Mouse released with reset
bool tools::mouse_clicked(const int button, bool reset) {
  bool old_released = MouseListener::mouse_released & button;

  if (reset) {
    MouseListener::mouse_released &= 0 << button;
  }

  return old_released;
}
