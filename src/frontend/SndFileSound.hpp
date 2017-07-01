#pragma once

#include "Sound.hpp"

namespace snd {
struct SndFileSound : public Sound {
  SndFileSound(const char *filename);
  virtual void Load();
};
}
