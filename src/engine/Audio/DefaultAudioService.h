/**
 * DefaultAudioService
 * Allan Legemaate
 * Implementation of audio service
 * 30/10/2020
 **/

#ifndef ENGINE_AUDIO_DEFAULT_AUDIO_SERVICE_H
#define ENGINE_AUDIO_DEFAULT_AUDIO_SERVICE_H

#include <string>

#include "AudioService.h"
#include "Sound.h"
#include "Stream.h"

class DefaultAudioService : public AudioService {
 public:
  // Play audio
  virtual void playSound(const std::string& key,
                         const PlaySoundConfig& config) override;

  // Stop sound
  virtual void stopSound(const std::string& key) override;

  // Play stream
  virtual void playStream(const std::string key,
                          const bool loop = false) override;

  // Stop stream
  virtual void stopStream(const std::string& key) override;
};

#endif  // ENGINE_AUDIO_DEFAULT_AUDIO_SERVICE_H