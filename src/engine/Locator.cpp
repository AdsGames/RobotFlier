#include "Locator.h"

void Locator::initialize() {
  audio_service = &null_audio_service;
}

AudioService* Locator::getAudio() {
  return audio_service;
}

void Locator::provideAudio(AudioService* service) {
  if (service == nullptr) {
    audio_service = &null_audio_service;
  } else {
    audio_service = service;
  }
}
