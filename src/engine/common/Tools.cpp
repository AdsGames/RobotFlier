#include "Tools.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>

#include <fstream>
#include <iostream>

#include "../input/MouseListener.h"

// A function to streamline error reporting in file loading
void tools::abort_on_error(const std::string& message,
                           const std::string& title) {
  al_show_native_message_box(nullptr, "Error", title.c_str(), message.c_str(),
                             nullptr, ALLEGRO_MESSAGEBOX_ERROR);
  exit(-1);
}

// Log message to console
void tools::log_message(const std::string& message, const bool debug) {
  if (debug) {
#ifdef Debug
    std::cout << message << "\n";
#endif
  } else {
    std::cout << message << "\n";
  }
}
