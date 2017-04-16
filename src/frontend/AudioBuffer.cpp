#include "AudioBuffer.hpp"
#include "Log.hpp"

#include "WAVSound.hpp"
#include "FLACSound.hpp"

#include <cstring>

AudioBuffer::AudioBuffer()
{}

AudioBuffer::~AudioBuffer()
{}

void AudioBuffer::Init(const char *file) {
  FLACSound wav(file);
  wav.Load();
  alGenBuffers(1, &buffer); ALERROR
  alBufferData(buffer, wav.format, wav.data, wav.size, wav.freq); ALERROR
  wav.Clear();
}

void AudioBuffer::Clear() {
  alDeleteBuffers(1, &buffer); ALERROR
}
