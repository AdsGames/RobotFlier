#include "Locator.h"

#include <stdexcept>

AudioService& Locator::getAudio() {
  if (!audio_service.get()) {
    throw std::runtime_error("Audio service not found");
  }
  return *audio_service;
}

AssetManager& Locator::getAsset() {
  if (!asset_service.get()) {
    throw std::runtime_error("Asset service not found");
  }
  return *asset_service;
}

Window& Locator::getWindow() {
  if (!window_service.get()) {
    throw std::runtime_error("Window service not found");
  }
  return *window_service;
}

SettingManager& Locator::getSettings() {
  if (!setting_service.get()) {
    throw std::runtime_error("Config service not found");
  }
  return *setting_service;
}