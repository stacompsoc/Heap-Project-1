#pragma once

#include <cstdlib>
#include <glm/glm.hpp>
#include "incaudio.h"
#include "AudioSource.hpp"
#include "AudioBuffer.hpp"

namespace al {
class Audio {
  ALCdevice *device = NULL;
  ALCcontext *context = NULL;
  AudioSource musicbox;
  AudioBuffer theme;
public:
  Audio();
  ~Audio();
  void Init();
  void ALVersion();
  static void ALListDevices();
  void SetListener(glm::vec3 position, glm::vec3 facing);
  void Play();
  void Stop();
  void Clear();
};
}
