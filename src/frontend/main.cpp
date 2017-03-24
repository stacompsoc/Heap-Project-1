#include "Window.hpp"

int main(int argc, char *argv[]) {
  Window w(960, 960);
  w.gl_version();
  w.idle();
}
