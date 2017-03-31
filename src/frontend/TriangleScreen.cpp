#include "TriangleScreen.hpp"
#include "Log.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "Storage.hpp"

TriangleScreen::TriangleScreen(Window *win):
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
  size_t tex_idx = Storage::inst()->AddTexture("textures/triangle.tga");
  Storage::inst()->textures()[tex_idx].AttachToShader(triangle_program);
}

void TriangleScreen::Display() {
  triangle_program.Use();
  Storage::inst()->textures()[0].Bind();
  tri.Draw();
  Storage::inst()->textures()[0].Unbind();
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
