#ifndef ENGINE_AUDIO_DEFAULT_AUDIO_SERVICE_H
#define ENGINE_AUDIO_DEFAULT_AUDIO_SERVICE_H

#include <map>
#include <string>

#include "AudioService.h"
#include "Sound.h"
#include "Stream.h"

class DefaultAudioService : public AudioService {
 public:
  void playSound(const std::string& key, const PlaySoundConfig& config);
  void stopSound(const std::string& key);

  void playStream(const std::string key, const bool loop = false);
  void stopStream(const std::string& key);
};

#endif  // ENGINE_AUDIO_DEFAULT_AUDIO_SERVICE_H