#include "Window.hpp"
#include "Debug.hpp"
#include "Logger.hpp"
#include "Storage.hpp"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>
#include <unistd.h>
#include <string>

Window::Window():
  width_(0), height_(0),
  spacescreen(this),
  trianglescreen(this),
  menuscreen(this),
  current_screen(NULL)
{}

Window::~Window()
{}

size_t Window::width() const {
  return width_;
}

size_t Window::height() const {
  return height_;
}

void Window::start() {
  Logger::Setup("frontend.log");
  Logger::MirrorLog(stderr);
  init_glfw();
  init_glew();
  init_controls();
  audio.Init();
  GLVersion();
}

void Window::init_glfw() {
  glfwSetErrorCallback(glfw_error_callback);
  int rc = glfwInit();
  ASSERT(rc == 1);

  vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  ASSERT(vidmode != NULL);
  width_ = vidmode->width;
  height_ = vidmode->height;

  /* glfwWindowHint(GLFW_SAMPLES, 4); */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

  window = glfwCreateWindow(width(), height(), "Planetarium", NULL, NULL);
  ASSERT(window != NULL);
  window_reference[window] = this;
  glfwMakeContextCurrent(window); GLERROR
  glfwSetKeyCallback(window, glfw_keypress_callback); GLERROR
  glfwSetWindowSizeCallback(window, glfw_size_callback); GLERROR
  glfwSetMouseButtonCallback(window, glfw_mouse_button_callback); GLERROR
  glfwSetScrollCallback(window, glfw_mouse_scroll_callback); GLERROR
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
  Logger::Info("Renderer: %s\n", renderer);
  Logger::Info("OpenGL version supported %s\n", version);
  Logger::Info("Supported OpenGL extensions:\n");
  GLint no_exts;
  glGetIntegerv(GL_NUM_EXTENSIONS, &no_exts);
  for(GLint i = 0; i < no_exts; ++i)
    Logger::Info("\t%s\n", glGetStringi(GL_EXTENSIONS, i));
}

void Window::Init() {
  Switch();
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

void Window::Resize(float new_width, float new_height) {
  width_ = new_width, height_ = new_height;
  current_screen->Resize();
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
  ASSERT(current_screen != NULL);
  current_screen->Resize();
}

void Window::Keyboard() {
  current_screen->Keyboard();
}

void Window::KeyboardEvent(int key, int scancode, int action, int mods) {
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if(action == GLFW_PRESS)
    current_screen->KeyPress(key, scancode, mods);
  if(action == GLFW_RELEASE)
    current_screen->KeyRelease(key, scancode, mods);
}

void Window::Mouse(double x, double y) {
  current_screen->Mouse(x, y);
}

void Window::MouseClick(double x, double y, int button, int action, int mods) {
}

void Window::MouseScroll(double xoffset, double yoffset) {
  current_screen->MouseScroll(xoffset, yoffset);
}

void Window::Clear() {
  /* trianglescreen.Clear(); */
  menuscreen.Clear();
  spacescreen.Clear();
  Storage::Clear();
  window_reference.erase(window);
  glfwTerminate(); GLERROR
  current_screen = NULL;
  audio.Clear();
  Logger::Close();
}
