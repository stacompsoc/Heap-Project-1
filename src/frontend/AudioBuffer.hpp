#pragma once

#include <cstdlib>
#include "incaudio.h"

#include "Sound.hpp"
#include "File.hpp"

struct AudioBuffer {
  ALuint buffer = 0;

  void *data = NULL;
  ALsizei size = 0;
  ALsizei freq = 0;
  ALenum format = 0;

  AudioBuffer();
  ~AudioBuffer();
  Sound *NewSound(File &&snd);
  void Init(const char *file);
  void Clear();
};
