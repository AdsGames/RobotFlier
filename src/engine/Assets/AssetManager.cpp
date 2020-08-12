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
  loaded_image[key] = Texture(path);
  tools::log_message("[Asset Manager] Loading image: " + key);
}

/**
 * Load audio from disk and assign key
 * @param key, unique id to assign to sound
 * @param path, path to file
 */
void AssetManager::loadAudio(const std::string& key, const std::string& path) {
  loaded_audio[key] = Sound(path);
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
  loaded_font[key] = Font(path, size);
  tools::log_message("[Asset Manager] Loading font: " + key);
}

/**
 * Load stream from disk and assign key
 * @param key, unique id to assign to istreammage
 * @param path, path to file
 */
void AssetManager::loadStream(const std::string& key, const std::string& path) {
  loaded_stream[key] = Stream(path);
  tools::log_message("[Asset Manager] Loading stream: " + key);
}

/**
 * Get image reference
 * @param key, key of asset to find
 */
const Texture& AssetManager::getImage(const std::string& key) {
  try {
    return loaded_image.at(key);
  } catch (...) {
    throw std::runtime_error("Could not find image asset " + key);
  }
}

/**
 * Get audio reference
 * @param key, key of asset to find
 */
const Sound& AssetManager::getAudio(const std::string& key) {
  try {
    return loaded_audio.at(key);
  } catch (...) {
    throw std::runtime_error("Could not find audio asset " + key);
  }
}

/**
 * Get font reference
 * @param key, key of asset to find
 */
const Font& AssetManager::getFont(const std::string& key) {
  try {
    return loaded_font.at(key);
  } catch (...) {
    throw std::runtime_error("Could not find font asset " + key);
  }
}

/**
 * Get stream reference
 * @param key, key of asset to find
 */
const Stream& AssetManager::getStream(const std::string& key) {
  try {
    return loaded_stream.at(key);
  } catch (...) {
    throw std::runtime_error("Could not find stream asset " + key);
  }
}
