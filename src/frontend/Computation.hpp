#pragma once

#include <string>

#include "File.hpp"
#include "MemBuffer.hpp"
#include "ComputeProgram.hpp"

namespace cl {

class Computation {
  cl_platform_id plat_id = 0;
  cl_device_id dev_id = 0;
  cl_context context = NULL;
  cl_command_queue cq = NULL;
  Program program;
  Computation &self = (*this);
public:
  Computation(std::string &&fname, std::string &&kernel_name);
  ~Computation();
  void init();
  void init_gl();
  template <typename T> void attach(T value) { program.set_kernel_arg(value); }
  template <typename T, cl_int OPTIONS> void attach(MemBuffer<T, OPTIONS> &mem) {
    if(!mem.active())
      mem.init();
    program.set_kernel_arg(mem);
  }
  template <typename T, cl_int OPTIONS = CL_MEM_READ_WRITE>
  MemBuffer<T,OPTIONS> make_membuf(T *host_ptr, size_t size, bool alloc = false) {
    return cl::MemBuffer<T, OPTIONS>(context, cq, host_ptr, size, alloc);
  }
  void execute(size_t N);
  void set_queue();
  void clear();
};

}
