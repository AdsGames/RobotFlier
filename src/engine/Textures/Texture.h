/**
 * Texture
 * Allan Legemaate
 * Wrapper for allegro bitmap
 * Easy interface to interact with bitmaps
 * 10/08/2020
 **/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>

class Texture {
 public:
  Texture();
  Texture(const std::string path);
  virtual ~Texture();

  void load(const std::string path);
  void create(const int width, const int height);

  void draw(const int x, const int y, const int flags);

  int getWidth();
  int getHeight();

 private:
  static ALLEGRO_BITMAP* loadBitmap(const std::string& file);

  ALLEGRO_BITMAP* texture;
};

#endif  // TEXTURE_H
