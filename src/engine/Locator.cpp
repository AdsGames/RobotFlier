#include "Locator.h"

AudioService& Locator::getAudio() {
  return *audio_service;
}

AssetManager& Locator::getAsset() {
  return *asset_service;
}
