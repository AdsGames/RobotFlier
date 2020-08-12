#include "Stream.h"

#include "../Common/Tools.h"

// Init global gain
bool Stream::globalGain = 1.0f;

// Ctor
Stream::Stream() : stream(nullptr) {}

Stream::Stream(const std::string& path) : Stream() {
  load(path);
}

// Dtor
Stream::~Stream() {
  if (stream) {
    // al_drain_audio_stream(stream);
    // al_destroy_audio_stream(stream);
  }
}

/**
 * Load and assign audio file to given path
 * @param path, path to audio file
 */
void Stream::load(const std::string& path) {
  stream = loadStream(path);
}

/**
 * Play Stream if it exists
 * @param gain, floating point gain
 * @param pan, left right balance
 * @param speed, playback speed/frequency
 * @param loop, loop status
 */
void Stream::play(const bool loop) {
  if (!stream) {
    return;
  }

  float stream_length = al_get_audio_stream_length_secs(stream);
  ALLEGRO_PLAYMODE playMode =
      loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE;

  al_set_audio_stream_loop_secs(stream, 0.0f, stream_length);
  al_set_audio_stream_playmode(stream, playMode);
  al_attach_audio_stream_to_mixer(stream, al_get_default_mixer());
}

/**
 * Stop stream
 */
void Stream::stop() {
  if (!stream) {
    return;
  }

  al_detach_audio_stream(stream);
}

/**
 * Return sample play status
 */
bool Stream::isPlaying() {
  return al_get_audio_stream_playing(stream);
}

/**
 * Set global gain of Stream effects
 * @param gain, global gain
 */
void Stream::setGlobalGain(const float gain) {
  Stream::globalGain = gain;
}

/**
 * Load sample from file
 * @param file, path to audio file
 */
ALLEGRO_AUDIO_STREAM* Stream::loadStream(const std::string& file) {
  // Attempt to load
  ALLEGRO_AUDIO_STREAM* temp_stream =
      al_load_audio_stream(file.c_str(), 4, 2048);

  if (!temp_stream) {
    tools::abort_on_error("There was an error loading " + file + "\nOh no :(",
                          "Loading Error");
  }

  return temp_stream;
}