#pragma once

#include "Sound.hpp"

struct SndFileSound : public Sound {
  SndFileSound(const char *filename);
  virtual void Load();
};
