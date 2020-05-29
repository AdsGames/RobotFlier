#include "tools.h"

#include <allegro5/allegro_ttf.h>

// Error handling loading functions
// Checks if file exists
ALLEGRO_BITMAP* load_bitmap_ex(std::string file) {
  ALLEGRO_BITMAP* temp_image = nullptr;

  if (!(temp_image = al_load_bitmap(file.c_str())))
    abort_on_error(std::string(
        "Cannot find image " + file +
        "\nTry reinstalling from adsgames.net/download/robotflier"));

  return temp_image;
}

// Checks if file exists
ALLEGRO_SAMPLE* load_sample_ex(std::string file) {
  ALLEGRO_SAMPLE* temp_sample = nullptr;

  if (!(temp_sample = al_load_sample(file.c_str())))
    abort_on_error(std::string(
        "Cannot find sample " + file +
        "\nTry reinstalling from adsgames.net/download/robotflier"));

  return temp_sample;
}

// Checks if file exists
ALLEGRO_FONT* load_font_ex(std::string file, int size, int flags) {
  ALLEGRO_FONT* temp_font;

  if (!(temp_font = al_load_ttf_font(file.c_str(), size, flags))) {
    abort_on_error(std::string(
        "Cannot find font " + file +
        "\nTry reinstalling from adsgames.net/download/robotflier"));
  }

  return temp_font;
}

// A function to streamline error reporting in file loading
void abort_on_error(std::string message) {
  al_show_native_message_box(nullptr, "Error", "Warning", message.c_str(),
                             nullptr, ALLEGRO_MESSAGEBOX_YES_NO);
  exit(-1);
}

// Random number generator. Use int random(highest,lowest);
int random(int newLowest, int newHighest) {
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber;  // this doens't work on linux =
                     // lowest+int(range*rand()/(RAND_MAX + 1.0));
  randomNumber = rand() % range + lowest;
  return randomNumber;
}

// Function to check for collision
bool collision(float xMin1,
               float xMax1,
               float xMin2,
               float xMax2,
               float yMin1,
               float yMax1,
               float yMin2,
               float yMax2) {
  if (xMin1 < xMax2 && yMin1 < yMax2 && xMin2 < xMax1 && yMin2 < yMax1) {
    return true;
  }

  return false;
}
