#include "Sound.hpp"
#include "Log.hpp"

Sound::Sound(const char *filename):
  filename(filename)
{}

Sound::~Sound()
{}

void Sound::Clear() {
  ASSERT(data != NULL);
  delete data;
}
