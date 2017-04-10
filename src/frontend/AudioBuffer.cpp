#include "AudioBuffer.hpp"
#include "Log.hpp"

#include <cstring>

AudioBuffer::AudioBuffer()
{}

AudioBuffer::~AudioBuffer()
{}

void AudioBuffer::Init(const char *file) {
  ALbyte filename[strlen(file)];
  memcpy(filename, file, strlen(file) + 1);
  alutLoadWAVFile(filename, &format, &data, &size, &freq); ALERROR
  //ASSERT(alutGetError() == ALUT_ERROR_NO_ERROR);
  alGenBuffers(1, &buffer); ALERROR
  alBufferData(buffer, format, data, size, freq); ALERROR
}

void AudioBuffer::Clear() {
  alDeleteBuffers(1, &buffer); ALERROR
}
