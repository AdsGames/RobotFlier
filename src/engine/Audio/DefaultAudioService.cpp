#include "DefaultAudioService.h"

#include "../Core.h"

void DefaultAudioService::playSound(const std::string& key,
                                    const PlaySoundConfig& config) {
  Sound sound = Engine::asset_manager.getAudio(key);
  sound.play(config);
}

void DefaultAudioService::stopSound(const std::string& key) {
  Sound sound = Engine::asset_manager.getAudio(key);
}

void DefaultAudioService::playStream(const std::string key, const bool loop) {
  Stream stream = Engine::asset_manager.getStream(key);
  stream.play(loop);
}

void DefaultAudioService::stopStream(const std::string& key) {
  Stream stream = Engine::asset_manager.getStream(key);
  stream.stop();
}
