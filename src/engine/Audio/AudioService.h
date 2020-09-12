#ifndef ENGINE_AUDIO_AUDIO_SERVICE_H
#define ENGINE_AUDIO_AUDIO_SERVICE_H

#include <map>
#include <string>

#include "Sound.h"
#include "Stream.h"

class AudioService {
 public:
  virtual void playSound(const std::string& key,
                         const PlaySoundConfig& config = PlaySoundConfig()) = 0;
  virtual void stopSound(const std::string& key) = 0;

  virtual void playStream(const std::string key, const bool loop = false) = 0;
  virtual void stopStream(const std::string& key) = 0;

 private:
  int volume;
  int detune;
};

#endif  // ENGINE_AUDIO_AUDIO_SERVICE_H