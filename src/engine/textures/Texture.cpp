#include "Texture.h"

#include "../common/Tools.h"

// Ctor
Texture::Texture() : bitmap(nullptr) {}

Texture::Texture(const std::string& path) {
  load(path);
}

// Dtor
Texture::~Texture() {
  if (bitmap) {
    // al_destroy_bitmap(texture);
  }
}

/**
 * Load texture from file
 * @param path, path to file
 */
void Texture::load(const std::string& path) {
  bitmap = loadBitmap(path);
}

/**
 * Create texture with specified dimensions
 * @param width, width of texture
 * @param height, height of texture
 */
void Texture::create(const int width, const int height) {
  bitmap = al_create_bitmap(width, height);
}

/**
 * Return height of loaded texture
 */
int Texture::getHeight() const {
  if (!bitmap) {
    return 0;
  }

  return al_get_bitmap_height(bitmap);
}

/**
 * Return if it exists
 */
bool Texture::exists() const {
  return bitmap != nullptr;
}

/**
 * Return width of loaded texture
 */
int Texture::getWidth() const {
  if (!bitmap) {
    return 0;
  }

  return al_get_bitmap_width(bitmap);
}

/**
 * Draw texture to screen
 * @param x, x position to draw to
 * @param y, y position to draw to
 * @param flags, config flags passed to al_draw_bitmap
 */
void Texture::draw(const int x, const int y, const int flags) const {
  if (!bitmap) {
    return;
  }

  al_draw_bitmap(bitmap, x, y, flags);
}

/**
 * Draw scaled texture to screen
 * @param x, x position to draw to
 * @param y, y position to draw to
 * @param width, width to scale to
 * @param height, height to scale to
 * @param flags, config flags passed to al_draw_bitmap
 */
void Texture::drawScaled(const int x,
                         const int y,
                         const int width,
                         const int height,
                         const int flags) const {
  if (!bitmap) {
    return;
  }

  al_draw_scaled_bitmap(bitmap, 0, 0, getWidth(), getHeight(), x, y, width,
                        height, flags);
}

ALLEGRO_COLOR Texture::getPixel(const int x, const int y) const {
  return al_get_pixel(this->bitmap, x, y);
}

/**
 * Load bitmap from file
 * @param file, path to image
 */
ALLEGRO_BITMAP* Texture::loadBitmap(const std::string& file) {
  // Attempt to load
  ALLEGRO_BITMAP* temp_bitmap = al_load_bitmap(file.c_str());

  if (!temp_bitmap) {
    tools::abort_on_error(
        "There was an error loading " + file + "... \nSorry...",
        "Loading Error");
  }

  return temp_bitmap;
}