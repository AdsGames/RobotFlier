/**
 * Sound
 * Danny Van Stemp
 * Wrapper for allegro sample
 * Easy interface to interact with samples
 * 23/11/2018
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

  int getWidth();
  int getHeight();

 private:
  static ALLEGRO_BITMAP* loadBitmap(const std::string file);

  ALLEGRO_BITMAP* texture;
};

#endif  // TEXTURE_H
