#include <cstdio>

#include "ShaderProgram.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

void gl::Program::print_info_log() {
  int max_length = 2048;
  int actual_length = 0;
  char program_log[2048];
  glGetProgramInfoLog(program, max_length, &actual_length, program_log); GLERROR
  Logger::Info("program info log for GL index %u:\n%s", program, program_log);
}

static const char* GL_type_to_string(GLenum type) {
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

void gl::Program::print_all() {
  Logger::Info("--------------------\nshader program %d info:\n", program);
  int params = -1;
  glGetProgramiv(program, GL_LINK_STATUS, &params);
  Logger::Info("GL_LINK_STATUS = %d\n", params);

  glGetProgramiv(program, GL_ATTACHED_SHADERS, &params);
  Logger::Info("GL_ATTACHED_SHADERS = %d\n", params);

  glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &params);
  Logger::Info("GL_ACTIVE_ATTRIBUTES = %d\n", params);
  for (int i = 0; i < params; i++) {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveAttrib (
      program,
      i,
      max_length,
      &actual_length,
      &size,
      &type,
      name
    );
    if(size > 1) {
      for(int j = 0; j < size; j++) {
        char long_name[64];
        sprintf(long_name, "%s[%d]", name, j);
        int location = glGetAttribLocation(program, long_name);
        Logger::Info("  %d) type:%s name:%s location:%d\n",
               i, GL_type_to_string(type), long_name, location);
      }
    } else {
      int location = glGetAttribLocation(program, name);
      Logger::Info("  %d) type:%s name:%s location:%d\n",
             i, GL_type_to_string(type), name, location);
    }
  }

  glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &params);
  Logger::Info("GL_ACTIVE_UNIFORMS = %d\n", params);
  for(int i = 0; i < params; i++) {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveUniform(
    program,
    i,
    max_length,
    &actual_length,
    &size,
    &type,
    name
    );
    if(size > 1) {
    for(int j = 0; j < size; j++) {
      char long_name[64];
      sprintf(long_name, "%s[%d]", name, j);
      int location = glGetUniformLocation(program, long_name);
      Logger::Info("  %d) type:%s name:%s location:%d\n",
         i, GL_type_to_string(type), long_name, location);
    }
    } else {
    int location = glGetUniformLocation(program, name);
    Logger::Info("  %d) type:%s name:%s location:%d\n",
         i, GL_type_to_string(type), name, location);
    }
  }
}

bool gl::Program::is_valid() {
  glValidateProgram(program);
  int params = -1;
  glGetProgramiv(program, GL_VALIDATE_STATUS, &params);
  Logger::Info("program %d GL_VALIDATE_STATUS = %d\n", program, params);
  print_info_log();
  print_all();
  if (GL_TRUE != params) {
    return false;
  }
  return true;
}
