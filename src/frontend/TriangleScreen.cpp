#include "TriangleScreen.hpp"
#include "Debug.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "Storage.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"

TriangleScreen::TriangleScreen(gl::Window *win):
  Screen(win),
  triangle_program({"triangle.vert", "triangle.geom", "triangle.frag"}),
  tri()
{}

TriangleScreen::~TriangleScreen()
{}

void TriangleScreen::Init() {
  GLfloat position[] = {
    -0.5, -0.5, 0.0,
    0.0, 0.5, 0.0,
    0.5, -0.5, 0.0,
  };
  GLfloat texcoords[] = {
    0.0, 0.0,
    0.5, 1.0,
    1.0, 0.0,
  };
  /* tri.Init(position, 0); */
  tri.Init(position, texcoords);
  triangle_program.Init({"vposition", "vtexcoords"});
  tex_idx = Storage::AddTexture("textures/triangle.tga");
  Sprite<gl::Texture>::Access(tex_idx).AttachToShader(triangle_program);
}

void TriangleScreen::Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); GLERROR
  triangle_program.Use();
  Sprite<gl::Texture>::Access(tex_idx).Bind();
  tri.Draw();
  gl::Texture::Unbind();
}

void TriangleScreen::Keyboard() {
  if(glfwGetKey(win_->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(win_->window, true);
  }
}

void TriangleScreen::Mouse(double x, double y) {
}

void TriangleScreen::Clear() {
  tri.Clear();
  triangle_program.Clear();
}
