#include "AssetManager.h"

#include <algorithm>
#include <stdexcept>

#include "../Locator.h"

// Constructor
AssetManager::AssetManager() {}

// Destructor
AssetManager::~AssetManager() {}

// Load image from disk and assign key
void AssetManager::loadImage(const std::string& key, const std::string& path) {
  Locator::getLogger().log("[Asset Manager] Loading image: " + key);

  try {
    loaded_image[key] = Texture(path);
  } catch (std::runtime_error) {
    throw std::runtime_error("Could not load asset " + key);
  }
}

// Load audio from disk and assign key
void AssetManager::loadAudio(const std::string& key, const std::string& path) {
  Locator::getLogger().log("[Asset Manager] Loading audio: " + key);

  try {
    loaded_audio[key] = Sound(path);
  } catch (std::runtime_error) {
    throw std::runtime_error("Could not load asset " + key);
  }
}

// Load font from disk and assign key
void AssetManager::loadFont(const std::string& key,
                            const std::string& path,
                            const int size) {
  Locator::getLogger().log("[Asset Manager] Loading font: " + key);

  try {
    loaded_font[key] = Font(path, size);
  } catch (std::runtime_error) {
    throw std::runtime_error("Could not load asset " + key);
  }
}

// Load stream from disk and assign key
void AssetManager::loadStream(const std::string& key, const std::string& path) {
  Locator::getLogger().log("[Asset Manager] Loading stream: " + key);

  try {
    loaded_stream[key] = Stream(path);
  } catch (std::runtime_error) {
    throw std::runtime_error("Could not load asset " + key);
  }
}

// Get image reference
const Texture& AssetManager::getImage(const std::string& key) {
  try {
    return loaded_image.at(key);
  } catch (std::out_of_range) {
    throw std::runtime_error("Could not find image asset " + key);
  }
}

// Get audio reference
const Sound& AssetManager::getAudio(const std::string& key) {
  try {
    return loaded_audio.at(key);
  } catch (std::out_of_range) {
    throw std::runtime_error("Could not find audio asset " + key);
  }
}

// Get font reference
const Font& AssetManager::getFont(const std::string& key) {
  try {
    return loaded_font.at(key);
  } catch (std::out_of_range) {
    throw std::runtime_error("Could not find font asset " + key);
  }
}

// Get stream reference
const Stream& AssetManager::getStream(const std::string& key) {
  try {
    return loaded_stream.at(key);
  } catch (std::out_of_range) {
    throw std::runtime_error("Could not find stream asset " + key);
  }
}
