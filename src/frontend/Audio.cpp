#include "Audio.hpp"
#include "Log.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Audio::Audio():
  musicbox()
{}

Audio::~Audio()
{}

void Audio::Init() {
  ASSERT(device == NULL);
  device = alcOpenDevice(NULL);
  ASSERT(device != NULL);
  context = alcCreateContext(device, NULL);
  int res = alcMakeContextCurrent(context);
  ASSERT(res);
  theme.Init("sounds/theme.wav");
  musicbox.Init(glm::vec3(0, 0, 1), AL_TRUE);
  SetListener(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0));
  musicbox.SetBuffer(theme.buffer);
}

void Audio::ALVersion() {
  ALboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT"); ALERROR
  ASSERT(enumeration == AL_TRUE);
  //
}

void Audio::ALListDevices() {
  const ALCchar *devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER); ALERROR
  const ALCchar *device = devices, *next = devices + 1;
  std::cout << "Devices list:" << std::endl;
  std::cout << "-------------" << std::endl;
  while(device != NULL && *device != '\0' && next != NULL && *next != '\0') {
    std::cout << *device << std::endl;
    size_t len = strlen(device);
    device += len + 1;
    next += len + 2;
  }
  std::cout << "-------------" << std::endl;
}

void Audio::SetListener(glm::vec3 position, glm::vec3 facing) {
  alListener3f(AL_POSITION, position.x, position.y, position.z); ALERROR
  alListener3f(AL_VELOCITY, 0, 0, 0); ALERROR
  ALfloat buffer[6];
  memcpy(buffer, glm::value_ptr(position), sizeof(ALfloat) * 3);
  memcpy(buffer + 3, glm::value_ptr(facing), sizeof(ALfloat) * 3);
  alListenerfv(AL_ORIENTATION, buffer); ALERROR
}

void Audio::Play() {
  musicbox.Play();
}

void Audio::Stop() {
  musicbox.Stop();
}

void Audio::Clear() {
  musicbox.Clear();
  theme.Clear();
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);
}
