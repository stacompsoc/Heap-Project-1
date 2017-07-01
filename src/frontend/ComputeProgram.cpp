#include "ComputeProgram.hpp"
#include "Debug.hpp"

cl::Program::Program(std::string &fname, std::string &kernel_name):
  file(fname.c_str()), kernel_name(kernel_name)
{}

cl::Program::operator cl_program() {
  return program;
}

void cl::Program::init(cl_context ctx, cl_device_id dev) {
  const char *source = file.load_text();
  const size_t len = file.length();
  cl_int ret;
  program = clCreateProgramWithSource(ctx, 1, &source, &len, &ret); CLERROR
  ret = clBuildProgram(program, 1, &dev, NULL, NULL, NULL); CLERROR
  kernel = clCreateKernel(self, kernel_name.c_str(), &ret); CLERROR
  free((char *)source);
}

void cl::Program::execute(cl_command_queue cq, size_t global_workgroup_size) {
  cl_int ret = clEnqueueNDRangeKernel(cq, kernel, 1, NULL, &global_workgroup_size, NULL, 0, NULL, NULL); CLERROR
  ret = clFinish(cq); CLERROR
}

void cl::Program::clear() {
  cl_int ret;
  ret = clReleaseKernel(kernel); CLERROR
  ret = clReleaseProgram(program); CLERROR
}

cl::Program::~Program()
{}
