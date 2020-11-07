#ifndef ENGINE_AUDIO_AUDIO_SERVICE_H
#define ENGINE_AUDIO_AUDIO_SERVICE_H

#include <string>

#include "Sound.h"
#include "Stream.h"

/**
 * @brief Default audio service, other audio services should inherit from this
 * class.
 *
 * @author Allan Legemaate
 * @date 30/10/2020
 */
class AudioService {
 public:
  virtual ~AudioService(){};

  /**
   * @brief Play sound by id
   *
   * @param key Id of sound to play
   * @param config Play configuration
   */
  virtual void playSound(const std::string& key,
                         const PlaySoundConfig& config = PlaySoundConfig());

  /**
   * @brief Play audio stream by id
   *
   * @param key Id of stream to play
   * @param loop Loop mode, true for looping, false for one shot
   */
  virtual void playStream(const std::string& key, const bool loop = false);

  /**
   * @brief Stop stream by id. Stops all instances of stream currently playing.
   *
   * @param key Id of stream to stop
   */
  virtual void stopStream(const std::string& key);
};

#endif  // ENGINE_AUDIO_AUDIO_SERVICE_H