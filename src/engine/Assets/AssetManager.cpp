#include "AssetManager.h"

#include <allegro/config.h>
#include <algorithm>

#include <iostream>

#include "../Common/Tools.h"

/*
 * C string to C++ string
 */
std::string cStringToCpp(const char* str) {
  return str ? str : "";
}

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
 * Load asset file, and assets into memory
 * @param file, path to file
 */
void AssetManager::load(const std::string file) {
  // Load config from disk
  ALLEGRO_CONFIG* config = al_load_config_file(file.c_str());
  ALLEGRO_CONFIG_SECTION* iterator = nullptr;
  std::string sectionName = al_get_first_config_section(config, &iterator);

  // Load specific config sections
  loadImages(config, "images");
  loadAudio(config, "audio");
  loadAudio(config, "streams");
  loadFonts(config, "fonts");
}

/**
 * Load images from images section
 * @param section, pointer to images section
 */
void AssetManager::loadImages(ALLEGRO_CONFIG* config,
                              const std::string sectionName) {
  ALLEGRO_CONFIG_ENTRY* iterator = nullptr;
  std::string entryName = cStringToCpp(
      al_get_first_config_entry(config, sectionName.c_str(), &iterator));

  // Load individual assets
  while (iterator) {
    tools::log_message("[Asset Manager] Loading image: " + entryName);

    std::string fileLocation = cStringToCpp(
        al_get_config_value(config, sectionName.c_str(), entryName.c_str()));

    loaded_image.push_back({
        Texture(fileLocation),
        entryName,
    });

    entryName = cStringToCpp(al_get_next_config_entry(&iterator));
  }
}

/**
 * Load audio from audio section
 * @param section, pointer to audio section
 */
void AssetManager::loadAudio(ALLEGRO_CONFIG* config,
                             const std::string sectionName) {
  ALLEGRO_CONFIG_ENTRY* iterator = nullptr;

  std::string entryName = cStringToCpp(
      al_get_first_config_entry(config, sectionName.c_str(), &iterator));

  // Load individual assets
  while (iterator) {
    tools::log_message("[Asset Manager] Loading audio: " + entryName);

    std::string fileLocation = cStringToCpp(
        al_get_config_value(config, sectionName.c_str(), entryName.c_str()));

    loaded_audio.push_back({
        Sound(fileLocation),
        entryName,
    });

    entryName = cStringToCpp(al_get_next_config_entry(&iterator));
  }
}

/**
 * Load fonts from fonts section
 * @param section, pointer to fonts section
 */
void AssetManager::loadFonts(ALLEGRO_CONFIG* config,
                             const std::string sectionName) {
  ALLEGRO_CONFIG_ENTRY* iterator = nullptr;
  std::string entryName = cStringToCpp(
      al_get_first_config_entry(config, sectionName.c_str(), &iterator));

  // Load individual assets
  while (iterator) {
    tools::log_message("[Asset Manager] Loading font: " + entryName);

    std::string fileLocation = cStringToCpp(
        al_get_config_value(config, sectionName.c_str(), entryName.c_str()));

    entryName = cStringToCpp(al_get_next_config_entry(&iterator));
  }
}

/**
 * Get allegro image pointer
 * @param key, key of asset to find
 */
const Texture& AssetManager::getImage(std::string key) {
  auto it = std::find_if(
      loaded_image.begin(), loaded_image.end(),
      [key](const AssetContainer<Texture>& asset) { return asset.key == key; });

  if (it == loaded_image.end()) {
    throw std::string("Could not find image asset " + key);
  }

  return (*it).data;
}

/**
 * Get allegro audio pointer
 * @param key, key of asset to find
 */
const Sound& AssetManager::getAudio(std::string key) {
  auto it = std::find_if(
      loaded_audio.begin(), loaded_audio.end(),
      [key](const AssetContainer<Sound>& asset) { return asset.key == key; });

  if (it == loaded_audio.end()) {
    throw std::string("Could not find audio asset " + key);
  }

  return (*it).data;
}

/**
 * Get allegro font pointer
 * @param key, key of asset to find
 */
const ALLEGRO_FONT* AssetManager::getFont(std::string key) {
  auto it = std::find_if(loaded_font.begin(), loaded_font.end(),
                         [key](const AssetContainer<ALLEGRO_FONT*>& asset) {
                           return asset.key == key;
                         });

  if (it == loaded_font.end()) {
    throw std::string("Could not find font asset " + key);
  }

  return (*it).data;
}
