#pragma once

#include <string>
#include "incaudio.h"

namespace snd {
struct Sound {
  std::string filename;
  short *data = NULL;
  ALsizei size = 0;
  ALsizei freq = 0;
  ALenum format = 0;

  Sound(const char *filename);
  virtual ~Sound();
  virtual void Load() = 0;
  void Clear();
};
}
