#include <cstdlib>
#include <unistd.h>
#include <string>

#include "Window.hpp"
#include "Storage.hpp"
#include "Camera.hpp"
#include "Log.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Window::Window(size_t width, size_t height):
  width_(width), height_(height),
  spacescreen(this),
  trianglescreen(this),
  menuscreen(this),
  current_screen(NULL)
{
}

size_t Window::width() const {
  return width_;
}

size_t Window::height() const {
  return height_;
}

void Window::start() {
  init_glfw();
  init_glew();
  init_controls();
  audio.Init();
  /* log_gl_params(); */
}

void Window::init_glfw() {
  int rc;
  rc = restart_gl_log();
  ASSERT(rc);
  glfwSetErrorCallback(glfw_error_callback);
  rc = glfwInit();
  ASSERT(rc == 1);

  /* glfwWindowHint(GLFW_SAMPLES, 4); */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
  // open a window and create its OpenGL context
  window = glfwCreateWindow(width(), height(), "Planetarium", NULL, NULL);
  ASSERT(window != NULL);
  glfwMakeContextCurrent(window); GLERROR
}

void Window::init_glew() {
  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  GLuint res = glewInit(); GLERROR
    ASSERT(res == GLEW_OK);
}

void Window::init_controls() {
  // ensure we can capture the escape key
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); GLERROR
    /* glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); GLERROR */
}

void Window::GLVersion() {
  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); GLERROR // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); GLERROR // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);
  printf("Supported OpenGL extensions:\n");
  GLint no_exts;
  glGetIntegerv(GL_NUM_EXTENSIONS, &no_exts);
  for(GLint i = 0; i < no_exts; ++i) {
    putchar('\t');
    const char* ext = (const char*)glGetStringi(GL_EXTENSIONS, i);
    puts(ext);
  }
}

void Window::Init() {
  /* current_screen = &trianglescreen; */
  /* current_screen = &spacescreen; */
  current_screen = &menuscreen;
  start();
  Storage::Setup();
  /* trianglescreen.Init(); */
  spacescreen.Init();
  menuscreen.Init();
}

void Window::Idle() {
  double m_x, m_y;
  audio.Play();
  while(!glfwWindowShouldClose(window)) {
    Display();
    Keyboard();
    glfwGetCursorPos(window, &m_x, &m_y);
    Mouse(m_x, m_y);
    if(current_screen->should_close)
      Switch();
  }
  audio.Stop();
}

void Window::Display() {
  current_screen->Display();
  if(!current_screen->should_close) {
    glfwPollEvents(); GLERROR
    glfwSwapBuffers(window); GLERROR
  }
}

void Window::Switch() {
  if(current_screen == NULL) {
    current_screen = &menuscreen;
  } else if(current_screen == &menuscreen) {
    current_screen = &spacescreen;
    spacescreen.should_close = false;
  } else if(current_screen == &spacescreen) {
    current_screen = &menuscreen;
    menuscreen.should_close = false;
  } else {
    glfwSetWindowShouldClose(window, true);
  }
}

void Window::Keyboard() {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  current_screen->Keyboard();
}

void Window::Mouse(double x, double y) {
  current_screen->Mouse(x, y);
}

void Window::Clear() {
  /* trianglescreen.Clear(); */
  menuscreen.Clear();
  spacescreen.Clear();
  Storage::Clear();
  glfwTerminate(); GLERROR
  current_screen = NULL;
  audio.Clear();
}

Window::~Window()
{}
