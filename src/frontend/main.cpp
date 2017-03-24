#include <cstdlib>

#include "Window.hpp"

int main(int argc, char *argv[]) {
  srand(time(NULL));
  Window w(960, 960);
  w.gl_version();
  w.idle();
  w.clear();
}
