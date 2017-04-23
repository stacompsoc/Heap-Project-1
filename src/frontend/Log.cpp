#include <ctime>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include <string>

#include "Log.hpp"

char *log_file = NULL;
FILE *log_file_ptr = NULL;

char *strdup(const char *s) {
  int len = (strlen(s) + 1) * sizeof(char);
  char *s2 = (char *)malloc(len);
  memcpy(s2, s, len);
  return s2;
}

bool restart_gl_log(const char *filename) {
  log_file = strdup(filename);
#ifndef NDEBUG
  truncate(log_file, 0);
  log_file_ptr = fopen(log_file, "a");
  if(log_file_ptr == NULL) {
    fprintf(stderr,
      "ERROR: could not open GL_LOG_FILE log file %s for writing\n",
      log_file);
    return false;
  }
  time_t now = time(NULL);
  char* date = ctime(&now);
  fprintf(log_file_ptr, "GL_LOG_FILE log. local time %s\n", date);
  fflush(log_file_ptr);
#endif
  return true;
}

void mirror_log(FILE *another) {
  dup2(fileno(another), fileno(log_file_ptr));
  if(errno) {
    perror("error");
    errno=0;
  }
}

bool gl_log(const char* message, ...) {
#ifndef NDEBUG
  if(log_file_ptr == NULL)
    fprintf(stderr, "error: cannot log into NULL file"),abort();
  va_list argptr;
  va_start(argptr, message);
  vfprintf(log_file_ptr, message, argptr);
  va_end(argptr);
#endif
  return true;
}

bool gl_log_err(const char* message, ...) {
#ifndef NDEBUG
  va_list argptr;
  va_start(argptr, message);
  vfprintf(stderr, message, argptr);
  va_end(argptr);
#endif
  return true;
}

void close_gl_log() {
  fclose(log_file_ptr);
  log_file_ptr = NULL;
  free(log_file);
  log_file = NULL;
}

void glfw_error_callback(int error, const char* description) {
#ifndef NDEBUG
  gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
#endif
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
  gl_log("GL Context Params:\n");
  char msg[256];
  // integers - only works if the order is 0-10 integer return types
  for (int i = 0; i < 10; i++) {
    int v = 0;
    glGetIntegerv(params[i], &v);
    gl_log("%s %i\n", names[i], v);
  }
  // others
  int v[2];
  v[0] = v[1] = 0;
  glGetIntegerv(params[10], v);
  gl_log("%s %i %i\n", names[10], v[0], v[1]);
  unsigned char s = 0;
  glGetBooleanv(params[11], &s);
  gl_log("%s %u\n", names[11], (unsigned int)s);
  gl_log("-----------------------------\n");
#endif
}

const char* GL_type_to_string(GLenum type) {
  switch(type) {
    case GL_BOOL: return "bool";
    case GL_INT: return "int";
    case GL_FLOAT: return "float";
    case GL_FLOAT_VEC2: return "vec2";
    case GL_FLOAT_VEC3: return "vec3";
    case GL_FLOAT_VEC4: return "vec4";
    case GL_FLOAT_MAT2: return "mat2";
    case GL_FLOAT_MAT3: return "mat3";
    case GL_FLOAT_MAT4: return "mat4";
    case GL_SAMPLER_2D: return "sampler2D";
    case GL_SAMPLER_3D: return "sampler3D";
    case GL_SAMPLER_CUBE: return "samplerCube";
    case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
    default: break;
  }
  return "other";
}

void explain_glerror(GLenum code) {
  std::string err;
  switch(code) {
    case GL_NO_ERROR:
      err = "no error";
    break;
    case GL_INVALID_ENUM:
      err = "invalid enum";
    break;
    case GL_INVALID_VALUE:
      err = "invalid value";
    break;
    case GL_INVALID_OPERATION:
      err = "invalid operation";
    break;
    case GL_STACK_OVERFLOW:
      err = "stack overflow";
    break;
    case GL_STACK_UNDERFLOW:
      err = "stack underflow";
    break;
    case GL_OUT_OF_MEMORY:
      err = "out of memory";
    break;
    case GL_TABLE_TOO_LARGE:
      err = "table too large";
    break;
    default:
      err = "unknown_error " + std::to_string(code);
    break;
  }
  std::cerr << err << std::endl;
}

void explain_alerror(ALenum code) {
  std::string err;
  switch(code) {
    case 40962:
      err = "invalid enum";
    break;
    case 40963:
      err = "invalid format";
    break;
  }
  std::cerr << "alerror: " << err << " (" << code << ")" << std::endl;
}
