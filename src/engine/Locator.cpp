#include "Locator.h"

#include "common/Exceptions.h"

AudioService& Locator::getAudio() {
  if (!audio_service.get()) {
    throw CoreServiceLookupException("Audio service not found");
  }
  return *audio_service;
}

AssetManager& Locator::getAsset() {
  if (!asset_service.get()) {
    throw CoreServiceLookupException("Asset service not found");
  }
  return *asset_service;
}

Window& Locator::getWindow() {
  if (!window_service.get()) {
    throw CoreServiceLookupException("Window service not found");
  }
  return *window_service;
}

SettingManager& Locator::getSettings() {
  if (!setting_service.get()) {
    throw CoreServiceLookupException("Config service not found");
  }
  return *setting_service;
}

Logger& Locator::getLogger() {
  if (!logger_service.get()) {
    throw CoreServiceLookupException("Logger service not found");
  }
  return *logger_service;
}