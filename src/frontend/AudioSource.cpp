#include "AudioSource.hpp"
#include "Debug.hpp"

al::AudioSource::AudioSource()
{}

al::AudioSource::~AudioSource()
{}

void al::AudioSource::Init(glm::vec3 position, ALboolean looping) {
  alGenSources(1, &source); ALERROR
  alSourcef(source, AL_PITCH, 1); ALERROR
  alSourcef(source, AL_GAIN, 1); ALERROR
  alSource3f(source, AL_POSITION, position.x, position.y, position.z); ALERROR
  alSource3f(source, AL_VELOCITY, 0, 0, 0); ALERROR
  alSourcei(source, AL_LOOPING, looping); ALERROR
}

void al::AudioSource::SetBuffer(ALuint buffer) {
  alSourcei(source, AL_BUFFER, buffer); ALERROR
}

void al::AudioSource::Play() {
  alSourcePlay(source); ALERROR
  ALint source_state = 0;
  alGetSourcei(source, AL_SOURCE_STATE, &source_state); ALERROR
  while(source_state != AL_PLAYING) {
    alGetSourcei(source, AL_SOURCE_STATE, &source_state); ALERROR
  }
}

void al::AudioSource::Stop() {
  alSourceStop(source); ALERROR
}

void al::AudioSource::Clear() {
  alDeleteSources(1, &source); ALERROR
}
