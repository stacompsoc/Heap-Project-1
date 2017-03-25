#include <cstdlib>
#include <unistd.h>
#include <string>

#include "Window.hpp"
#include "Sprite.hpp"
#include "Planetarium.hpp"
#include "Camera.hpp"

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
  win_ = glfwCreateWindow(width, height, "Planetarium", NULL, NULL);
  ASSERT(win_ != NULL);
  glfwMakeContextCurrent(win_); GLERROR
}

void Window::init_glew() {
  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  GLuint res = glewInit(); GLERROR
  ASSERT(res == GLEW_OK);
}

void Window::init_controls() {
  // ensure we can capture the escape key
  glfwSetInputMode(win_, GLFW_STICKY_KEYS, GL_TRUE); GLERROR
  glfwSetInputMode(win_, GLFW_CURSOR, GLFW_CURSOR_DISABLED); GLERROR
}

Window::Window(size_t width, size_t height):
  width(width), height(height),
  shader_program("shader.vert", "shader.frag")
{
  start();
}

void Window::GLVersion() {
  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); GLERROR // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); GLERROR // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);
}

void Window::Idle() {
  glEnable(GL_DEPTH_TEST); GLERROR
  glDepthFunc(GL_LESS); GLERROR
  Sprite::Setup();
  Camera::Setup(width, height);
  Planetarium::Setup();
  /* GLfloat position[] = { */
  /*   -0.5, -0.5, 0.0, */
  /*   0.0, 0.5, 0.0, */
  /*   0.5, -0.5, 0.0, */
  /* }; */
  Planetarium::inst()->AddPlanet(Sphere(glm::vec3(0.0f, 0.0f, 0.0f), .3));
  Planetarium::inst()->AddPlanet(Sphere(glm::vec3(0.5f, 0.5f, 0.0f), .1));
  Planetarium::inst()->AddPlanet(Sphere(glm::vec3(0.5f, 0.5f, 0.5f), .2));
  Planetarium::inst()->AddPlanet(Sphere(glm::vec3(0.5f, -0.5f, 0.7f), .1));
  shader_program.Init({"vposition", "vcolor"});
  glEnable(GL_CULL_FACE); GLERROR // cull face
  glCullFace(GL_BACK); GLERROR // cull back face
  glFrontFace(GL_CW); GLERROR // GL_CCW for counter clock-wise
  while(!glfwWindowShouldClose(win_)) {
    Display();
    Keyboard();
  }
}

void Window::Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GLERROR
  Camera::inst()->AttachToShader(shader_program);
  shader_program.Use(); GLERROR
  Camera::inst()->Update();
  Planetarium::inst()->Draw();
  glfwPollEvents(); GLERROR
  glfwSwapBuffers(win_); GLERROR
}

void Window::Keyboard() {
  Camera *cam = Camera::inst();
  if(glfwGetKey(win_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(win_, true);
  } else if(glfwGetKey(win_, GLFW_KEY_UP)) {
    cam->yx -= M_PI / 10.;
  } else if(glfwGetKey(win_, GLFW_KEY_DOWN)) {
    cam->yx += M_PI / 10.;
  } else if(glfwGetKey(win_, GLFW_KEY_LEFT)) {
    cam->zx -= M_PI/10.;
  } else if(glfwGetKey(win_, GLFW_KEY_RIGHT)) {
    cam->zx += M_PI/10.;
  } else if(glfwGetKey(win_, GLFW_KEY_EQUAL)) {
    cam->dist *= 1.05;
  } else if(glfwGetKey(win_, GLFW_KEY_MINUS)) {
    cam->dist /= 1.05;
  } else if(glfwGetKey(win_, '0')) {
    cam->dist = 1., cam->zx = 0., cam->yx = M_PI/2.;
  }
  cam->Update();
}

void Window::Clear() {
  shader_program.Clear(); GLERROR
  Planetarium::Clear();
  Sprite::Clear();
  Camera::Clear();
  glfwTerminate(); GLERROR
}

Window::~Window()
{}
