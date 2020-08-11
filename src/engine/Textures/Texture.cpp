#include "Texture.h"

#include "../Common/Tools.h"

// Ctor
Texture::Texture() : texture(nullptr) {}

Texture::Texture(const std::string path) {
  load(path);
}

// Dtor
Texture::~Texture() {
  if (texture) {
    // al_destroy_bitmap(texture);
  }
}

/**
 * Load texture from file
 * @param path, path to file
 */
void Texture::load(std::string path) {
  texture = loadBitmap(path);
}

/**
 * Create texture with specified dimensions
 * @param width, width of texture
 * @param height, height of texture
 */
void Texture::create(const int width, const int height) {
  texture = al_create_bitmap(width, height);
}

/**
 * Return height of loaded texture
 */
int Texture::getHeight() {
  if (!texture) {
    return 0;
  }

  return al_get_bitmap_height(texture);
}

/**
 * Return width of loaded texture
 */
int Texture::getWidth() {
  if (!texture) {
    return 0;
  }

  return al_get_bitmap_width(texture);
}

/**
 * Draw texture to screen
 * @param x, x position to draw to
 * @param y, y position to draw to
 * @param flags, config flags passed to al_draw_bitmap
 */
void Texture::draw(const int x, const int y, const int flags) {
  if (!texture) {
    return;
  }

  al_draw_bitmap(texture, x, y, flags);
}

/**
 * Load bitmap from file
 * @param file, path to image
 */
ALLEGRO_BITMAP* Texture::loadBitmap(const std::string& file) {
  // Attempt to load
  ALLEGRO_BITMAP* temp_image = al_load_bitmap(file.c_str());

  if (!temp_image) {
    tools::abort_on_error(
        "There was an error loading " + file + "... \nSorry...",
        "Loading Error");
  }

  return temp_image;
}