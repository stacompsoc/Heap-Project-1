#pragma once

#include <type_traits>

#include "File.hpp"
#include "MemBuffer.hpp"

namespace cl {

struct Program {
  cl_program program = NULL;
  cl_kernel kernel = NULL;
  File file;
  std::string kernel_name;
  Program &self = *this;
  cl_int no_kernel_args = 0;

  Program(std::string &fname, std::string &kernel_name);
  ~Program();
  operator cl_program();
  void init(cl_context ctx, cl_device_id dev);

  template <typename T, cl_int OPTIONS>
  void set_kernel_arg(MemBuffer<T, OPTIONS> &mem) {
    cl_int ret = clSetKernelArg(kernel, no_kernel_args++, sizeof(cl_mem), &mem.dev_ptr); CLERROR
  }

  template <typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
  void set_kernel_arg(T value) {
    cl_int ret = clSetKernelArg(kernel, no_kernel_args++, sizeof(T), &value); CLERROR
  }

  void execute(cl_command_queue cq, size_t global_workgroup_size);
  void clear();
};

}
