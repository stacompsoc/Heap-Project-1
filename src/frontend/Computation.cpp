#include "Computation.hpp"
#include "Debug.hpp"

#include "incinterop.h"

#include "MemBuffer.hpp"

compute::Computation::Computation(std::string &&fname, std::string &&kernel_name):
  program(fname, kernel_name)
{}

void compute::Computation::init() {
  cl_int ret;
  cl_uint no_plats=0;
  cl_uint no_devs=0;
  ret = clGetPlatformIDs(1, &plat_id, &no_plats); CLERROR
  ret = clGetDeviceIDs(plat_id, CL_DEVICE_TYPE_DEFAULT, 1, &dev_id, &no_devs); CLERROR
  /* cl_context_properties platform, hRC, hDC; */
  /* cl_context_properties props[] = { */
  /*   CL_CONTEXT_PLATFORM, (cl_context_properties)platform, */
  /*   CL_GL_CONTEXT_KHR,   (cl_context_properties)hRC, */
  /*   CL_WGL_HDC_KHR,      (cl_context_properties)hDC, 0 */
  /* }; */
  /* size_t bytes = 0; */
  /* clGetGLContextInfoKHR(props, CL_DEVICES_FOR_GL_CONTEXT_KHR, 0, NULL, &bytes); */
  /* std::vector<cl_device_id> devs(bytes / sizeof(cl_device_id)); */
  /* clGetGLContextInfoKHR(props, CL_DEVICES_FOR_GL_CONTEXT_KHR, bytes, devs, NULL)); */
  /* for(size_t i = 0; i < devs.size(); ++i) */
  /* { */
  /*     //enumerating the devices for the type, names, CL_DEVICE_EXTENSIONS, etc */
  /*     clGetDeviceInfo(devs[i],CL_DEVICE_TYPE, …); */
  /*     … */
  /*     clGetDeviceInfo(devs[i],CL_DEVICE_EXTENSIONS,…); */
  /*     … */
  /* } */
  context = clCreateContext(NULL, 1, &dev_id, NULL, NULL, &ret); CLERROR
  program.init(context, dev_id);
  cq = clCreateCommandQueue(context, dev_id, 0, &ret); CLERROR
}

void compute::Computation::execute(size_t N) {
  program.execute(cq, N);
}

void compute::Computation::clear() {
  cl_int ret;
  ret = clReleaseCommandQueue(cq); CLERROR
  ret = clReleaseContext(context); CLERROR
}

compute::Computation::~Computation()
{}
