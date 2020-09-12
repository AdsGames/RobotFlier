#ifndef ENGINE_LOCATOR_H
#define ENGINE_LOCATOR_H

#include "Audio/AudioService.h"
#include "Audio/NullAudioService.h"

class Locator {
 public:
  static void initialize();

  static AudioService* getAudio();

  static void provideAudio(AudioService* service);

 private:
  static inline AudioService* audio_service = nullptr;
  static inline NullAudioService null_audio_service;
};

#endif  // ENGINE_LOCATOR_H