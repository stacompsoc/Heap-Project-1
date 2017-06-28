#include "ComputeProgram.hpp"
#include "Debug.hpp"

compute::Program::Program(std::string &fname, std::string &kernel_name):
  file(fname.c_str()), kernel_name(kernel_name)
{}

compute::Program::operator cl_program() {
  return program;
}

void compute::Program::init(cl_context ctx, cl_device_id dev) {
  const char *source = file.load_text();
  const size_t len = file.length();
  cl_int ret;
  program = clCreateProgramWithSource(ctx, 1, &source, &len, &ret); CLERROR
  ret = clBuildProgram(program, 1, &dev, NULL, NULL, NULL); CLERROR
  kernel = clCreateKernel(self, kernel_name.c_str(), &ret); CLERROR
  free((char *)source);
}

void compute::Program::execute(cl_command_queue cq, size_t global_workgroup_size) {
  cl_int ret;
  ret = clEnqueueNDRangeKernel(cq, kernel, 1, NULL, &global_workgroup_size, NULL, 0, NULL, NULL); CLERROR
}

void compute::Program::clear() {
  cl_int ret;
  ret = clReleaseKernel(kernel); CLERROR
  ret = clReleaseProgram(program); CLERROR
}

compute::Program::~Program()
{}
