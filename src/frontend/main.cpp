#include <cstdlib>
#include <unistd.h>

#include "Window.hpp"

int main(int argc, char *argv[]) {
  srand(time(NULL));
  gl::Window w;
  w.Init();
  w.Idle();
  w.Clear();
}
