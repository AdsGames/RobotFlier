#include "AudioService.h"

void AudioService::playSound(const std::string& key,
                             const PlaySoundConfig& config) {
  (void)(key);
  (void)(config);
};

void AudioService::stopSound(const std::string& key) {
  (void)(key);
};

void AudioService::playStream(const std::string key, const bool loop) {
  (void)(key);
  (void)(loop);
};

void AudioService::stopStream(const std::string& key) {
  (void)(key);
};