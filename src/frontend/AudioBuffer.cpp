#include "AudioBuffer.hpp"
#include "Log.hpp"

#include "WAVSound.hpp"

#include <cstring>

AudioBuffer::AudioBuffer()
{}

AudioBuffer::~AudioBuffer()
{}

void AudioBuffer::Init(const char *file) {
  ALbyte filename[strlen(file)];
  memcpy(filename, file, strlen(file) + 1);
  WAVSound wav(file);
  wav.Load();
  alGenBuffers(1, &buffer); ALERROR
  alBufferData(buffer, wav.format, wav.data, wav.size, wav.freq); ALERROR
  wav.Clear();
}

void AudioBuffer::Clear() {
  alDeleteBuffers(1, &buffer); ALERROR
}
