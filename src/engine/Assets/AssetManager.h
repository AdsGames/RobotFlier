/**
 * Asset Manager
 * Allan Legemaate
 * Container for resources
 * 05/08/2020
 **/

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <allegro5/allegro_font.h>
#include <string>
#include <vector>

#include "../Audio/Sound.h"
#include "../Textures/Texture.h"

template <class T>
struct AssetContainer {
 public:
  T data;
  std::string key;
};

class AssetManager {
 public:
  AssetManager();
  ~AssetManager();

  const Sound& getAudio(const std::string key);
  const Texture& getImage(const std::string key);
  const ALLEGRO_FONT* getFont(const std::string key);

  void load(const std::string file);

 private:
  void loadImages(ALLEGRO_CONFIG* config, const std::string sectionName);
  void loadAudio(ALLEGRO_CONFIG* config, const std::string sectionName);
  void loadFonts(ALLEGRO_CONFIG* config, const std::string sectionName);

  std::vector<AssetContainer<Sound>> loaded_audio;
  std::vector<AssetContainer<Texture>> loaded_image;
  std::vector<AssetContainer<ALLEGRO_FONT*>> loaded_font;
};

#endif  // ASSET_MANAGER_H
