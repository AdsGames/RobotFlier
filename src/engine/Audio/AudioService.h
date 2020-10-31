/**
 * AudioService
 * Allan Legemaate
 * Base audio service, virtual only
 * 30/10/2020
 **/

#ifndef ENGINE_AUDIO_AUDIO_SERVICE_H
#define ENGINE_AUDIO_AUDIO_SERVICE_H

#include <string>

#include "Sound.h"
#include "Stream.h"

class AudioService {
 public:
  // Play sound
  virtual void playSound(const std::string& key,
                         const PlaySoundConfig& config = PlaySoundConfig()) = 0;

  // Stop sound
  virtual void stopSound(const std::string& key) = 0;

  // Play stream
  virtual void playStream(const std::string key, const bool loop = false) = 0;

  // Stop stream
  virtual void stopStream(const std::string& key) = 0;
};

#endif  // ENGINE_AUDIO_AUDIO_SERVICE_H