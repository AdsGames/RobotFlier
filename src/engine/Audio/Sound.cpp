#include "Sound.h"

#include "../Common/Tools.h"

// Ctor
Sound::Sound() : sample(nullptr), sample_id(nullptr), is_playing(false) {}

Sound::Sound(const std::string path) : Sound() {
  load(path);
}

// Dtor
Sound::~Sound() {
  // al_destroy_sample(sample);
}

// Load WAV from file
void Sound::load(std::string path) {
  sample = loadSample(path);
}

// Play sound
void Sound::play(const float volume, const bool loop) {
  if (!sample) {
    return;
  }

  ALLEGRO_PLAYMODE playMode =
      loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE;
  is_playing = true;
  al_play_sample(sample, volume, 0.0, 1.0, playMode, sample_id);
}

// Stop sound
void Sound::stop() {
  if (!sample) {
    return;
  }

  al_stop_samples();
  is_playing = false;
}

bool Sound::isPlaying() {
  return is_playing;
}

// Load sample if exits, or throw error
ALLEGRO_SAMPLE* Sound::loadSample(std::string file) {
  // Attempt to load
  ALLEGRO_SAMPLE* temp_sample = al_load_sample(file.c_str());

  if (!temp_sample) {
    tools::abort_on_error("There was an error loading " + file + "\nOh no :(",
                          "Loading Error");
  }

  return temp_sample;
}