#include <cstdlib>
#include <unistd.h>
#include <string>

#include "Window.hpp"
#include "Storage.hpp"
#include "Planetarium.hpp"
#include "Camera.hpp"
#include "Log.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void Window::start() {
  init_glfw();
  init_glew();
  init_controls();
  /* log_gl_params(); */
}

void Window::init_glfw() {
  assert(restart_gl_log());
  glfwSetErrorCallback(glfw_error_callback);
  ASSERT(glfwInit() == 1);

  /* glfwWindowHint(GLFW_SAMPLES, 4); */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
  // open a window and create its OpenGL context
  window = glfwCreateWindow(width(), height(), "Planetarium", NULL, NULL);
  restart_gl_log();
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
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); GLERROR
}

Window::Window(size_t width, size_t height):
  width_(width), height_(height),
  spacescreen(this),
  trianglescreen(this),
  menuscreen(this),
  current_screen(NULL)
{
  current_screen = &spacescreen;
  start();
}

size_t Window::width() const {
  return width_;
}

size_t Window::height() const {
  return height_;
}

void Window::GLVersion() {
  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); GLERROR // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); GLERROR // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);
}

void Window::Init() {
  glEnable(GL_DEPTH_TEST); GLERROR
  glDepthFunc(GL_LESS); GLERROR
  Storage::Setup();
  current_screen->Init();
  /* glEnable(GL_CULL_FACE); GLERROR // cull face */
  /* glCullFace(GL_BACK); GLERROR // cull back face */
  /* glFrontFace(GL_CW); GLERROR // GL_CCW for counter clock-wise */
}

void Window::Idle() {
  while(!glfwWindowShouldClose(window)) {
    Display();
    Keyboard();
  }
}

void Window::Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GLERROR
  current_screen->Display();
  glfwPollEvents(); GLERROR
  glfwSwapBuffers(window); GLERROR
}

void Window::Keyboard() {
  current_screen->Keyboard();
}

void Window::Clear() {
  current_screen->Clear();
  Storage::Clear();
  glfwTerminate(); GLERROR
  current_screen = NULL;
}

Window::~Window()
{}
