#pragma once

#include <cstdlib>
#include "incaudio.h"

#include "Sound.hpp"
#include "File.hpp"

namespace al {
struct AudioBuffer {
  ALuint buffer = 0;

  void *data = NULL;
  ALsizei size = 0;
  ALsizei freq = 0;
  ALenum format = 0;

  AudioBuffer();
  ~AudioBuffer();
  snd::Sound *NewSound(File &&snd);
  void Init(const char *file);
  void Clear();
};
}
