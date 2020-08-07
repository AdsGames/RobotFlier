#include "Texture.h"

#include "../Common/Tools.h"

// Ctor
Texture::Texture() : texture(nullptr) {}

Texture::Texture(const std::string path) {
  load(path);
}

// Dtor
Texture::~Texture() {
  // al_destroy_bitmap(texture);
}

// Load WAV from file
void Texture::load(std::string path) {
  texture = loadBitmap(path);
}

// Get height
int Texture::getHeight() {
  return 0;
}

// Get width
int Texture::getWidth() {
  return 0;
}

// Load bitmap if exits, or throw error
ALLEGRO_BITMAP* Texture::loadBitmap(std::string file) {
  // Attempt to load
  ALLEGRO_BITMAP* temp_image = al_load_bitmap(file.c_str());

  if (!temp_image) {
    tools::abort_on_error(
        "There was an error loading " + file + "... \nSorry...",
        "Loading Error");
  }

  return temp_image;
}