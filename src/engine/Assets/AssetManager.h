/**
 * Asset Manager
 * Allan Legemaate
 * Container for resources
 * 05/08/2020
 **/

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <string>
#include <vector>

#include "../Audio/Sound.h"
#include "../Audio/Stream.h"
#include "../Fonts/Font.h"
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

  const Sound& getAudio(const std::string& key);
  const Texture& getImage(const std::string& key);
  const Font& getFont(const std::string& key);
  const Stream& getStream(const std::string& key);

  void loadImage(const std::string& key, const std::string& path);
  void loadAudio(const std::string& key, const std::string& path);
  void loadFont(const std::string& key,
                const std::string& path,
                const int size);
  void loadStream(const std::string& key, const std::string& path);

 private:
  std::vector<AssetContainer<Sound>> loaded_audio;
  std::vector<AssetContainer<Texture>> loaded_image;
  std::vector<AssetContainer<Font>> loaded_font;
  std::vector<AssetContainer<Stream>> loaded_stream;
};

#endif  // ASSET_MANAGER_H
