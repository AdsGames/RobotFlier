/**
 * Asset Manager
 * Allan Legemaate
 * Container for resources
 * 05/08/2020
 **/

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>

#include "../Audio/Sound.h"
#include "../Audio/Stream.h"
#include "../Fonts/Font.h"
#include "../Textures/Texture.h"

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
  std::map<std::string, Sound> loaded_audio;
  std::map<std::string, Texture> loaded_image;
  std::map<std::string, Font> loaded_font;
  std::map<std::string, Stream> loaded_stream;
};

#endif  // ASSET_MANAGER_H
