#include "AssetManager.h"

#include <algorithm>
#include <stdexcept>

#include "../Common/Tools.h"

/**
 * Load assets from file
 */
AssetManager::AssetManager() {
  // Todo
}

/**
 * Unload assets
 */
AssetManager::~AssetManager() {
  // Todo
}

/**
 * Load image from disk and assign key
 * @param key, unique id to assign to image
 * @param path, path to file
 */
void AssetManager::loadImage(const std::string& key, const std::string& path) {
  loaded_image.push_back({
      Texture(path),
      key,
  });

  tools::log_message("[Asset Manager] Loading image: " + key);
}

/**
 * Load audio from disk and assign key
 * @param key, unique id to assign to sound
 * @param path, path to file
 */
void AssetManager::loadAudio(const std::string& key, const std::string& path) {
  loaded_audio.push_back({
      Sound(path),
      key,
  });

  tools::log_message("[Asset Manager] Loading audio: " + key);
}

/**
 * Load font from disk and assign key
 * @param key, unique id to assign to font
 * @param path, path to file
 */
void AssetManager::loadFont(const std::string& key,
                            const std::string& path,
                            const int size) {
  loaded_font.push_back({
      Font(path, size),
      key,
  });

  tools::log_message("[Asset Manager] Loading font: " + key);
}

/**
 * Load stream from disk and assign key
 * @param key, unique id to assign to istreammage
 * @param path, path to file
 */
void AssetManager::loadStream(const std::string& key, const std::string& path) {
  loaded_stream.push_back({
      Stream(path),
      key,
  });

  tools::log_message("[Asset Manager] Loading stream: " + key);
}

/**
 * Get image reference
 * @param key, key of asset to find
 */
const Texture& AssetManager::getImage(const std::string& key) {
  auto it = std::find_if(
      loaded_image.begin(), loaded_image.end(),
      [key](const AssetContainer<Texture>& asset) { return asset.key == key; });

  if (it == loaded_image.end()) {
    throw std::runtime_error("Could not find image asset " + key);
  }

  return (*it).data;
}

/**
 * Get audio reference
 * @param key, key of asset to find
 */
const Sound& AssetManager::getAudio(const std::string& key) {
  auto it = std::find_if(
      loaded_audio.begin(), loaded_audio.end(),
      [key](const AssetContainer<Sound>& asset) { return asset.key == key; });

  if (it == loaded_audio.end()) {
    throw std::runtime_error("Could not find audio asset " + key);
  }

  return (*it).data;
}

/**
 * Get font reference
 * @param key, key of asset to find
 */
const Font& AssetManager::getFont(const std::string& key) {
  auto it = std::find_if(
      loaded_font.begin(), loaded_font.end(),
      [key](const AssetContainer<Font>& asset) { return asset.key == key; });

  if (it == loaded_font.end()) {
    throw std::runtime_error("Could not find font asset " + key);
  }

  return (*it).data;
}

/**
 * Get stream reference
 * @param key, key of asset to find
 */
const Stream& AssetManager::getStream(const std::string& key) {
  auto it = std::find_if(
      loaded_stream.begin(), loaded_stream.end(),
      [key](const AssetContainer<Stream>& asset) { return asset.key == key; });

  if (it == loaded_stream.end()) {
    throw std::runtime_error("Could not find stream asset " + key);
  }

  return (*it).data;
}
