#include "AudioBuffer.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

#include "WAVSound.hpp"
#include "FLACSound.hpp"

#include <cstring>

al::AudioBuffer::AudioBuffer()
{}

al::AudioBuffer::~AudioBuffer()
{}

snd::Sound *al::AudioBuffer::NewSound(File &&snd) {
  if(snd.is_ext(".wav")) {
    return new snd::WAVSound(snd.name().c_str());
  } else if(snd.is_ext(".flac")) {
    return new snd::FLACSound(snd.name().c_str());
  }
  Logger::Error("unsupported file format for %s\n", snd.name().c_str());
  throw std::domain_error("unsupported music format for " + snd.name());
}

void al::AudioBuffer::Init(const char *file) {
  snd::Sound *snd = NewSound(File(file));
  snd->Load();
  alGenBuffers(1, &buffer); ALERROR
  alBufferData(buffer, snd->format, snd->data, snd->size, snd->freq); ALERROR
  snd->Clear();
  delete snd;
}

void al::AudioBuffer::Clear() {
  alDeleteBuffers(1, &buffer); ALERROR
}
