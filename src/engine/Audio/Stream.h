/**
 * Stream
 * Allan Legemaate
 * Wrapper for allegro sample including ability to store
 * stream pointer. Use for single instance sounds like music
 * 10/08/2020
 **/

#ifndef ENGINE_AUDIO_STREAM_H
#define ENGINE_AUDIO_STREAM_H

#include <allegro5/allegro_audio.h>
#include <string>

class Stream {
 public:
  Stream();
  explicit Stream(const std::string& path);

  virtual ~Stream();

  void play(const bool loop = false);
  void stop();

  void load(const std::string& path);

  bool isPlaying();

  static void setGlobalGain(const float gain);

 private:
  static ALLEGRO_AUDIO_STREAM* loadStream(const std::string& file);
  static bool globalGain;

  ALLEGRO_AUDIO_STREAM* stream;
};

#endif  // ENGINE_AUDIO_STREAM_H
