#include "Locator.h"

AudioService& Locator::getAudio() {
  return *audio_service;
}

AssetManager& Locator::getAsset() {
  return *asset_service;
}

Window& Locator::getWindow() {
  return *window_service;
}

SettingManager& Locator::getSettings() {
  return *setting_service;
}