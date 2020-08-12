#include "tools.h"

#include <allegro5/allegro_native_dialog.h>

#include "../constants/globals.h"

// A function to streamline error reporting in file loading
void abort_on_error(const std::string& message) {
  al_show_native_message_box(nullptr, "Error", "Warning", message.c_str(),
                             nullptr, ALLEGRO_MESSAGEBOX_YES_NO);
  exit(-1);
}

// Function to check for collision
bool collision(const float xMin1,
               const float xMax1,
               const float xMin2,
               const float xMax2,
               const float yMin1,
               const float yMax1,
               const float yMin2,
               const float yMax2) {
  if (xMin1 < xMax2 && yMin1 < yMax2 && xMin2 < xMax1 && yMin2 < yMax1) {
    return true;
  }

  return false;
}
