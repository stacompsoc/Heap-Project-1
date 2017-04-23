#include "SndFileSound.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

#include <cstring>
#include <sys/stat.h>
#include <sndfile.h>

SndFileSound::SndFileSound(const char *filename):
  Sound(strdup(filename))
{}

void SndFileSound::Load() {
  ASSERT(data == NULL);
  SF_INFO sfinfo;
  SNDFILE *sndfile = sf_open(filename.c_str(), SFM_READ, &sfinfo);
  if(sndfile == NULL)
    throw std::runtime_error("error opening file " + filename + ": " + sf_strerror(NULL));
  format = ((sfinfo.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);
  size = sfinfo.channels * sfinfo.frames;
  data = new short[size];
  freq = sfinfo.samplerate;
  sf_read_short(sndfile, data, size);
  size *= sizeof(short);
  Logger::Info("%lu %lu %lu\n", size, format, freq);
  sf_close(sndfile);
}
