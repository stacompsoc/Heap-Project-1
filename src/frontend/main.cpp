#include <cstdlib>
#include <unistd.h>

#include "Window.hpp"

int main(int argc, char *argv[]) {
  srand(time(NULL));
  Window w;
  w.Init();
  w.Idle();
  w.Clear();
}
