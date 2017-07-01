#include "Sound.hpp"
#include "Debug.hpp"

snd::Sound::Sound(const char *filename):
  filename(filename)
{}

snd::Sound::~Sound()
{}

void snd::Sound::Clear() {
  ASSERT(data != NULL);
  delete data;
}
