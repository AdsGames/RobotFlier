#include "Sound.h"

#include "../common/Tools.h"

// Init global gain
bool Sound::globalGain = 1.0f;

// Ctor
Sound::Sound() : sample(nullptr) {}

Sound::Sound(const std::string& path) : Sound() {
  load(path);
}

// Dtor
Sound::~Sound() {
  if (sample) {
    // al_destroy_sample(sample);
  }
}

/**
 * Load and assign audio file to given path
 * @param path, path to audio file
 */
void Sound::load(const std::string& path) {
  sample = loadSample(path);
}

/**
 * Play sound if it exists
 * @param gain, floating point gain
 * @param pan, left right balance
 * @param speed, playback speed/frequency
 * @param loop, loop status
 */
void Sound::play(const PlaySoundConfig& config) {
  if (!sample) {
    return;
  }

  ALLEGRO_PLAYMODE playMode =
      config.loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE;

  al_play_sample(sample, config.gain, config.pan, config.speed, playMode,
                 nullptr);
}

/**
 * Set global gain of sound effects
 * @param gain, global gain
 */
void Sound::setGlobalGain(const float gain) {
  Sound::globalGain = gain;
}

/**
 * Load sample from file
 * @param file, path to audio file
 */
ALLEGRO_SAMPLE* Sound::loadSample(const std::string& file) {
  // Attempt to load
  ALLEGRO_SAMPLE* temp_sample = al_load_sample(file.c_str());

  if (!temp_sample) {
    tools::abort_on_error("There was an error loading " + file + "\nOh no :(",
                          "Loading Error");
  }

  return temp_sample;
}