#pragma once

#include "Sound.hpp"

struct WAVSound : public Sound {
  WAVSound(const char *filename);
  void Load();
};
