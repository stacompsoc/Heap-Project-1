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
    case 40962: err = "invalid enum"; break;
    case 40963: err = "invalid format"; break;
  }
  std::cerr << "alerror: " << err << " (" << code << ")" << std::endl;
}

void explain_clerror(cl_int code) {
  std::string err;
  switch(code) {
    // run-time and JIT compiler errors
    case 0: err = "CL_SUCCESS"; break;
    case -1: err = "CL_DEVICE_NOT_FOUND"; break;
    case -2: err = "CL_DEVICE_NOT_AVAILABLE"; break;
    case -3: err = "CL_COMPILER_NOT_AVAILABLE"; break;
    case -4: err = "CL_MEM_OBJECT_ALLOCATION_FAILURE"; break;
    case -5: err = "CL_OUT_OF_RESOURCES"; break;
    case -6: err = "CL_OUT_OF_HOST_MEMORY"; break;
    case -7: err = "CL_PROFILING_INFO_NOT_AVAILABLE"; break;
    case -8: err = "CL_MEM_COPY_OVERLAP"; break;
    case -9: err = "CL_IMAGE_FORMAT_MISMATCH"; break;
    case -10: err = "CL_IMAGE_FORMAT_NOT_SUPPORTED"; break;
    case -11: err = "CL_BUILD_PROGRAM_FAILURE"; break;
    case -12: err = "CL_MAP_FAILURE"; break;
    case -13: err = "CL_MISALIGNED_SUB_BUFFER_OFFSET"; break;
    case -14: err = "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST"; break;
    case -15: err = "CL_COMPILE_PROGRAM_FAILURE"; break;
    case -16: err = "CL_LINKER_NOT_AVAILABLE"; break;
    case -17: err = "CL_LINK_PROGRAM_FAILURE"; break;
    case -18: err = "CL_DEVICE_PARTITION_FAILED"; break;
    case -19: err = "CL_KERNEL_ARG_INFO_NOT_AVAILABLE"; break;

    // compile-time errors
    case -30: err = "CL_INVALID_VALUE"; break;
    case -31: err = "CL_INVALID_DEVICE_TYPE"; break;
    case -32: err = "CL_INVALID_PLATFORM"; break;
    case -33: err = "CL_INVALID_DEVICE"; break;
    case -34: err = "CL_INVALID_CONTEXT"; break;
    case -35: err = "CL_INVALID_QUEUE_PROPERTIES"; break;
    case -36: err = "CL_INVALID_COMMAND_QUEUE"; break;
    case -37: err = "CL_INVALID_HOST_PTR"; break;
    case -38: err = "CL_INVALID_MEM_OBJECT"; break;
    case -39: err = "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR"; break;
    case -40: err = "CL_INVALID_IMAGE_SIZE"; break;
    case -41: err = "CL_INVALID_SAMPLER"; break;
    case -42: err = "CL_INVALID_BINARY"; break;
    case -43: err = "CL_INVALID_BUILD_OPTIONS"; break;
    case -44: err = "CL_INVALID_PROGRAM"; break;
    case -45: err = "CL_INVALID_PROGRAM_EXECUTABLE"; break;
    case -46: err = "CL_INVALID_KERNEL_NAME"; break;
    case -47: err = "CL_INVALID_KERNEL_DEFINITION"; break;
    case -48: err = "CL_INVALID_KERNEL"; break;
    case -49: err = "CL_INVALID_ARG_INDEX"; break;
    case -50: err = "CL_INVALID_ARG_VALUE"; break;
    case -51: err = "CL_INVALID_ARG_SIZE"; break;
    case -52: err = "CL_INVALID_KERNEL_ARGS"; break;
    case -53: err = "CL_INVALID_WORK_DIMENSION"; break;
    case -54: err = "CL_INVALID_WORK_GROUP_SIZE"; break;
    case -55: err = "CL_INVALID_WORK_ITEM_SIZE"; break;
    case -56: err = "CL_INVALID_GLOBAL_OFFSET"; break;
    case -57: err = "CL_INVALID_EVENT_WAIT_LIST"; break;
    case -58: err = "CL_INVALID_EVENT"; break;
    case -59: err = "CL_INVALID_OPERATION"; break;
    case -60: err = "CL_INVALID_GL_OBJECT"; break;
    case -61: err = "CL_INVALID_BUFFER_SIZE"; break;
    case -62: err = "CL_INVALID_MIP_LEVEL"; break;
    case -63: err = "CL_INVALID_GLOBAL_WORK_SIZE"; break;
    case -64: err = "CL_INVALID_PROPERTY"; break;
    case -65: err = "CL_INVALID_IMAGE_DESCRIPTOR"; break;
    case -66: err = "CL_INVALID_COMPILER_OPTIONS"; break;
    case -67: err = "CL_INVALID_LINKER_OPTIONS"; break;
    case -68: err = "CL_INVALID_DEVICE_PARTITION_COUNT"; break;

    // extension errors
    case -1000: err = "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR"; break;
    case -1001: err = "CL_PLATFORM_NOT_FOUND_KHR"; break;
    case -1002: err = "CL_INVALID_D3D10_DEVICE_KHR"; break;
    case -1003: err = "CL_INVALID_D3D10_RESOURCE_KHR"; break;
    case -1004: err = "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR"; break;
    case -1005: err = "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR"; break;
    case -1006: err = "CL_INVALID_D3D11_DEVICE_KHR"; break;
    case -1007: err = "CL_INVALID_D3D11_RESOURCE_KHR"; break;
    case -1008: err = "CL_D3D11_RESOURCE_ALREADY_ACQUIRED_KHR"; break;
    case -1009: err = "CL_D3D11_RESOURCE_NOT_ACQUIRED_KHR"; break;
    case -1010: err = "CL_INVALID_D3D9_DEVICE_NV or CL_INVALID_DX9_DEVICE_INTEL"; break;
    case -1011: err = "CL_INVALID_D3D9_RESOURCE_NV or CL_INVALID_DX9_RESOURCE_INTEL"; break;
    case -1012: err = "CL_D3D9_RESOURCE_ALREADY_ACQUIRED_NV or CL_DX9_RESOURCE_ALREADY_ACQUIRED_INTEL"; break;
    case -1013: err = "CL_D3D9_RESOURCE_NOT_ACQUIRED_NV  or CL_DX9_RESOURCE_NOT_ACQUIRED_INTEL"; break;
    case -1092: err = "CL_EGL_RESOURCE_NOT_ACQUIRED_KHR1"; break;
    case -1093: err = "CL_INVALID_EGL_OBJECT_KHR"; break;
    case -1094: err = "CL_INVALID_ACCELERATOR_INTEL"; break;
    case -1095: err = "CL_INVALID_ACCELERATOR_TYPE_INTEL"; break;
    case -1096: err = "CL_INVALID_ACCELERATOR_DESCRIPTOR_INTEL"; break;
    case -1097: err = "CL_ACCELERATOR_TYPE_NOT_SUPPORTED_INTEL"; break;
    case -1098: err = "CL_INVALID_VA_API_MEDIA_ADAPTER_INTEL"; break;
    case -1099: err = "CL_INVALID_VA_API_MEDIA_SURFACE_INTEL"; break;
    case -1100: err = "CL_VA_API_MEDIA_SURFACE_ALREADY_ACQUIRED_INTEL"; break;
    case -1101: err = "CL_VA_API_MEDIA_SURFACE_NOT_ACQUIRED_INTEL"; break;
    default: err = "Unknown OpenCL error"; break;
  }
  std::cerr << err << std::endl;
}
