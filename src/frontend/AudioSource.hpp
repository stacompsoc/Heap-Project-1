#pragma once

#include <glm/glm.hpp>
#include "incaudio.h"

struct AudioSource {
  ALuint source = 0;
  AudioSource();
  ~AudioSource();
  void Init(glm::vec3 position, ALboolean looping = AL_FALSE);
  void SetBuffer(ALuint buffer);
  void Play();
  void Stop();
  void Clear();
};
