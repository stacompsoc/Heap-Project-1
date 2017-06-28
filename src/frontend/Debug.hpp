#pragma once

#include <iostream>

#include "incgraphics.h"
#include "incaudio.h"
#include "inccompute.h"

#define STR(x) #x
#define TOSTR(x) STR(x)
#define ERROR(format) fprintf(stderr, "error: " format "\n");

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define CODE_LOCATION "\033[1m" __FILE__ "\033[0m::\033[93m" TOSTRING(__LINE__) "\033[0m"
#define CONDITION_TOSTR(CONDITION) " ( \033[1;4m" STRINGIFY(CONDITION) "\033[0m )"

#define ASSERT(CONDITION) \
  if(!(CONDITION)) { \
    throw std::runtime_error("\033[1;91merror\033[0m at " CODE_LOCATION CONDITION_TOSTR(CONDITION)); \
  }

#ifndef NDEBUG

#define GLERROR { GLenum ret = glGetError(); if(ret != GL_NO_ERROR) { explain_glerror(ret); std::cerr << ret << std::endl; ASSERT(ret == GL_NO_ERROR); } };
#define ALERROR { GLenum ret = alGetError(); if(ret != GL_NO_ERROR) { explain_alerror(ret); std::cerr << ret << std::endl; ASSERT(ret == GL_NO_ERROR); } };
#define CLERROR if(ret != CL_SUCCESS) { explain_clerror(ret); std::cerr << ret << std::endl; ASSERT(ret == CL_SUCCESS); };

#else

#define GLERROR
#define ALERROR
#define CLERROR

#endif

void explain_glerror(GLenum code);
void explain_alerror(ALenum code);
void explain_clerror(cl_int code);
