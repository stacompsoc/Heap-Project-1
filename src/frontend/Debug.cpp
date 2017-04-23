#include "Debug.hpp"

#include <stdexcept>
#include <iostream>
#include <string>

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
