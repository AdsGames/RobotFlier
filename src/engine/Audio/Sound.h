/**
 * Sound
 * Danny Van Stemp
 * Wrapper for allegro sample
 * Easy interface to interact with samples
 * 23/11/2018
 **/

#ifndef SOUND_H
#define SOUND_H

#include <allegro5/allegro_audio.h>
#include <string>

class Sound {
 public:
  Sound();
  Sound(const std::string path);

  virtual ~Sound();

  void play(const float volume = 1.0f, const bool loop = false);
  void stop();

  void load(const std::string path);

  bool isPlaying();

 private:
  static ALLEGRO_SAMPLE* loadSample(const std::string file);

  ALLEGRO_SAMPLE* sample;
  ALLEGRO_SAMPLE_ID* sample_id;

  bool is_playing;
};

#endif  // SOUND_H
