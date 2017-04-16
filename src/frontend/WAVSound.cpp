#include "WAVSound.hpp"
#include "Log.hpp"
#include "incaudio.h"

#include <cstring>
#include <sys/stat.h>
#include <sndfile.h>

WAVSound::WAVSound(const char *filename):
  Sound(strdup(filename))
{}

static size_t file_length(std::string &filename) {
  struct stat st;
  stat(filename.c_str(), &st);
  return st.st_size;
}

void WAVSound::Load() {
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
  gl_log("%lu %lu %lu\n", size, format, freq);
  sf_close(sndfile);
}
