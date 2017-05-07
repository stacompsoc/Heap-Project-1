#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include <string>

#include "Debug.hpp"
#include "Logger.hpp"

char *log_file = NULL;
FILE *log_file_ptr = NULL;

char *strdup(const char *s) {
  int len = (strlen(s) + 1) * sizeof(char);
  char *s2 = (char *)malloc(len);
  memcpy(s2, s, len);
  return s2;
}

Logger::Logger(const char *filename):
  filename(filename)
{
#ifndef NDEBUG
  truncate(this->filename.c_str(), 0);
  file = fopen(this->filename.c_str(), "a");
  ASSERT(file != NULL);
#endif
}

Logger::~Logger() {
  if(file != NULL)
    fclose(file);
}

void Logger::Write(const char *fmt, va_list args) {
#ifndef NDEBUG
  if(file == NULL)return;
  ASSERT(file != NULL);
  vfprintf(file, fmt, args);
  fflush(file);
#endif
}

void Logger::WriteFmt(const char *prefix, const char *fmt, va_list args) {
#ifndef NDEBUG
  if(file == NULL)return;
  ASSERT(file != NULL);
  vfprintf(file, (std::string() + prefix + fmt).c_str(), args);
#endif
}

Logger *Logger::instance = NULL;
void Logger::Setup(const char *filename) {
  if(instance == NULL)
    instance = new Logger(filename);
  Logger::Info("Started log %s\n", filename);
}

void Logger::Say(const char *fmt, ...) {
  ASSERT(instance != NULL);
  va_list argptr;
  va_start(argptr, fmt);
  instance->Write(fmt, argptr);
  va_end(argptr);
}

void Logger::Info(const char *fmt, ...) {
  ASSERT(instance != NULL);
  va_list argptr;
  va_start(argptr, fmt);
  instance->WriteFmt("INFO: ", fmt, argptr);
  va_end(argptr);
}

void Logger::Warning(const char *fmt, ...) {
  ASSERT(instance != NULL);
  va_list argptr;
  va_start(argptr, fmt);
  instance->WriteFmt("WARN: ", fmt, argptr);
  va_end(argptr);
}

void Logger::Error(const char *fmt, ...) {
  ASSERT(instance != NULL);
  va_list argptr;
  va_start(argptr, fmt);
  instance->WriteFmt("ERROR: ", fmt, argptr);
  va_end(argptr);
}

void Logger::MirrorLog(FILE *redir) {
  ASSERT(instance != NULL);
  if(instance->file == NULL)
    return;
  dup2(fileno(redir), fileno(instance->file));
  if(errno) {
    perror("error");
    errno=0;
  }
}

void Logger::Close() {
  Logger::Info("Closing log %s", instance->filename.c_str());
  ASSERT(instance != NULL);
  delete instance;
  instance = NULL;
}

void log_gl_params() {
#ifndef NDEBUG
  GLenum params[] = {
    GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
    GL_MAX_CUBE_MAP_TEXTURE_SIZE,
    GL_MAX_DRAW_BUFFERS,
    GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
    GL_MAX_TEXTURE_IMAGE_UNITS,
    GL_MAX_TEXTURE_SIZE,
    GL_MAX_VARYING_FLOATS,
    GL_MAX_VERTEX_ATTRIBS,
    GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
    GL_MAX_VERTEX_UNIFORM_COMPONENTS,
    GL_MAX_VIEWPORT_DIMS,
    GL_STEREO,
  };
  const char* names[] = {
    "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
    "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
    "GL_MAX_DRAW_BUFFERS",
    "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
    "GL_MAX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_TEXTURE_SIZE",
    "GL_MAX_VARYING_FLOATS",
    "GL_MAX_VERTEX_ATTRIBS",
    "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
    "GL_MAX_VIEWPORT_DIMS",
    "GL_STEREO",
  };
  Logger::Info("GL Context Params:\n");
  char msg[256];
  // integers - only works if the order is 0-10 integer return types
  for (int i = 0; i < 10; i++) {
    int v = 0;
    glGetIntegerv(params[i], &v);
    Logger::Info("%s %i\n", names[i], v);
  }
  // others
  int v[2];
  v[0] = v[1] = 0;
  glGetIntegerv(params[10], v);
  Logger::Info("%s %i %i\n", names[10], v[0], v[1]);
  unsigned char s = 0;
  glGetBooleanv(params[11], &s);
  Logger::Info("%s %u\n", names[11], (unsigned int)s);
  Logger::Info("-----------------------------\n");
#endif
}
