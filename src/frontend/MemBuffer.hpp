#pragma once

#include "Debug.hpp"

#include <type_traits>

namespace compute {

template <typename T, cl_int OPTIONS = CL_MEM_READ_WRITE>
class MemBuffer {
  cl_context ctx = NULL;
  cl_command_queue cq = NULL;
  size_t size_;


  bool host_alloc = false;
  MemBuffer<T, OPTIONS> &self = *this;
  bool is_active = false;
public:
  T *host_ptr = NULL;
  cl_mem dev_ptr = NULL;

  static constexpr bool
    can_read = (OPTIONS == CL_MEM_READ_WRITE || OPTIONS == CL_MEM_READ_ONLY),
    can_write = (OPTIONS == CL_MEM_READ_WRITE || OPTIONS == CL_MEM_WRITE_ONLY);

  MemBuffer(cl_context ctx, cl_command_queue cq, T *data, size_t size, bool host_alloc):
    ctx(ctx), cq(cq), host_ptr(data), size_(size), host_alloc(host_alloc)
  {
    if(host_alloc)
      host_ptr = new T[size];
  }

  T &operator[](size_t i) {
    return host_ptr[i];
  }

  size_t size() const {
    return size_;
  }

  bool active() const {
    return is_active;
  }

  void init() {
    cl_int ret;
    dev_ptr = clCreateBuffer(ctx, OPTIONS, size()*sizeof(T), NULL, &ret); CLERROR
    is_active = true;
  }

  operator cl_mem() {
    return dev_ptr;
  }

  template <typename = std::enable_if<can_write>>
  void set_data() {
    if(!is_active)
      init();
    cl_int ret = clEnqueueWriteBuffer(cq, dev_ptr, CL_TRUE, 0, size()*sizeof(T), host_ptr, 0, NULL, NULL); CLERROR
  }

  template <typename = std::enable_if<can_read>>
  void get_data() {
    ASSERT(is_active);
    cl_int ret = clEnqueueReadBuffer(cq, dev_ptr, CL_TRUE, 0, size()*sizeof(T), host_ptr, 0, NULL, NULL); CLERROR
  }

  void clear() {
    cl_int ret = clReleaseMemObject(self); CLERROR
    is_active = false;
  }

  ~MemBuffer() {
    if(is_active)
      clear();
    if(host_alloc)
      delete [] host_ptr;
  }
};

}
