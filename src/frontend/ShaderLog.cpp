#include <cstdio>

#include "ShaderProgram.hpp"
#include "Log.hpp"

void ShaderProgram::print_info_log() {
  int max_length = 2048;
  int actual_length = 0;
  char program_log[2048];
  glGetProgramInfoLog(program, max_length, &actual_length, program_log); GLERROR
  gl_log("program info log for GL index %u:\n%s", program, program_log);
}

void ShaderProgram::print_all() {
  gl_log("--------------------\nshader program %d info:\n", program);
  int params = -1;
  glGetProgramiv(program, GL_LINK_STATUS, &params);
  gl_log("GL_LINK_STATUS = %d\n", params);

  glGetProgramiv(program, GL_ATTACHED_SHADERS, &params);
  gl_log("GL_ATTACHED_SHADERS = %d\n", params);

  glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &params);
  gl_log("GL_ACTIVE_ATTRIBUTES = %d\n", params);
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
        gl_log("  %d) type:%s name:%s location:%d\n",
               i, GL_type_to_string(type), long_name, location);
      }
    } else {
      int location = glGetAttribLocation(program, name);
      gl_log("  %d) type:%s name:%s location:%d\n",
             i, GL_type_to_string(type), name, location);
    }
  }

  glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &params);
  gl_log("GL_ACTIVE_UNIFORMS = %d\n", params);
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
      gl_log("  %d) type:%s name:%s location:%d\n",
         i, GL_type_to_string(type), long_name, location);
    }
    } else {
    int location = glGetUniformLocation(program, name);
    gl_log("  %d) type:%s name:%s location:%d\n",
         i, GL_type_to_string(type), name, location);
    }
  }
}

bool ShaderProgram::is_valid() {
  glValidateProgram(program);
  int params = -1;
  glGetProgramiv(program, GL_VALIDATE_STATUS, &params);
  gl_log("program %d GL_VALIDATE_STATUS = %d\n", program, params);
  print_info_log();
  print_all();
  if (GL_TRUE != params) {
    return false;
  }
  return true;
}
