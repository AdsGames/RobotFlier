#include "Stream.h"

#include <exception>

// Constructor
Stream::Stream() : stream(nullptr) {}

// Constructor with path
Stream::Stream(const std::string& path) : Stream() {
  load(path);
}

// Load stream from file
void Stream::load(const std::string& path) {
  stream = loadStream(path);
}

// Play stream
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

// Stop stream
void Stream::stop() {
  if (!stream) {
    return;
  }

  al_detach_audio_stream(stream);
}

// Return if the audio is playing
bool Stream::isPlaying() const {
  return al_get_audio_stream_playing(stream);
}

// Load allegro sample from file
ALLEGRO_AUDIO_STREAM* Stream::loadStream(const std::string& file) {
  // Attempt to load
  ALLEGRO_AUDIO_STREAM* temp_stream =
      al_load_audio_stream(file.c_str(), 4, 2048);

  // Throw exception if file is not loaded
  if (!temp_stream) {
    throw std::runtime_error("There was an error loading stream " + file);
  }

  return temp_stream;
}