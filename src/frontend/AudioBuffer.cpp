#include "AudioBuffer.hpp"
#include "Log.hpp"

#include "WAVSound.hpp"
#include "FLACSound.hpp"

#include <cstring>

AudioBuffer::AudioBuffer()
{}

AudioBuffer::~AudioBuffer()
{}

Sound *AudioBuffer::NewSound(File &&snd) {
  if(snd.is_ext(".wav")) {
    return new WAVSound(snd.name().c_str());
  } else if(snd.is_ext(".flac")) {
    return new FLACSound(snd.name().c_str());
  }
  throw std::domain_error("error: unsupported file format");
}

void AudioBuffer::Init(const char *file) {
  Sound *snd = NewSound(File(file));
  snd->Load();
  alGenBuffers(1, &buffer); ALERROR
  alBufferData(buffer, snd->format, snd->data, snd->size, snd->freq); ALERROR
  snd->Clear();
  delete snd;
}

void AudioBuffer::Clear() {
  alDeleteBuffers(1, &buffer); ALERROR
}
