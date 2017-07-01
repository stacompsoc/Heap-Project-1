#include "Computation.hpp"
#include "Debug.hpp"

#include "incinterop.h"

#include "MemBuffer.hpp"

cl::Computation::Computation(std::string &&fname, std::string &&kernel_name):
  program(fname, kernel_name)
{}

void cl::Computation::init() {
  cl_int ret;
  {
    cl_uint no_plats=0;
    ret = clGetPlatformIDs(0, NULL, &no_plats); CLERROR
    cl_platform_id platforms[no_plats];
    ret = clGetPlatformIDs(no_plats, platforms, NULL); CLERROR
    plat_id = platforms[0];
  }
  {
    cl_uint no_devs=0;
    ret = clGetDeviceIDs(plat_id, CL_DEVICE_TYPE_DEFAULT, 0, NULL, &no_devs); CLERROR
    cl_device_id devices[no_devs];
    ret = clGetDeviceIDs(plat_id, CL_DEVICE_TYPE_DEFAULT, no_devs, devices, NULL); CLERROR
    dev_id = devices[0];
  }
  context = clCreateContext(NULL, 1, &dev_id, NULL, NULL, &ret); CLERROR
  program.init(context, dev_id);
  cq = clCreateCommandQueue(context, dev_id, 0, &ret); CLERROR
}

// interop is not implemented on most of the platforms
/* void cl::Computation::init_gl() { */
/*   cl_int ret; */
/*   cl_context_properties platform, hRC, hDC; */
/*   cl_context_properties props[] = { */
/*     CL_CONTEXT_PLATFORM, (cl_context_properties)platform, */
/*     CL_GL_CONTEXT_KHR,   (cl_context_properties)hRC, */
/*     CL_WGL_HDC_KHR,      (cl_context_properties)hDC, 0 */
/*   }; */
/*   size_t bytes = 0; */
/*   clGetGLContextInfoKHR(props, CL_DEVICES_FOR_GL_CONTEXT_KHR, 0, NULL, &bytes); */
/*   std::vector<cl_device_id> devs(bytes / sizeof(cl_device_id)); */
/*   clGetGLContextInfoKHR(props, CL_DEVICES_FOR_GL_CONTEXT_KHR, bytes, devs, NULL)); */
/*   for(size_t i = 0; i < devs.size(); ++i) */
/*   { */
/*       //enumerating the devices for the type, names, CL_DEVICE_EXTENSIONS, etc */
/*       clGetDeviceInfo(devs[i],CL_DEVICE_TYPE, …); */
/*       … */
/*       clGetDeviceInfo(devs[i],CL_DEVICE_EXTENSIONS,…); */
/*       … */
/*   } */
/*   context = clCreateContext(props, 1, &dev_id, NULL, NULL, &ret); CLERROR */
/*   program.init(context, dev_id); */
/*   cq = clCreateCommandQueue(context, dev_id, 0, &ret); CLERROR */
/* } */

void cl::Computation::execute(size_t N) {
  program.execute(cq, N);
}

void cl::Computation::clear() {
  cl_int ret;
  program.clear();
  ret = clReleaseCommandQueue(cq); CLERROR
  ret = clReleaseContext(context); CLERROR
}

cl::Computation::~Computation()
{}
