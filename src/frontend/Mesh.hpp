#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "incgraphics.h"

#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"

class Mesh  {
private:
  gl::Program program;
  gl::VertexArray vao;
  GLuint vbo=0, ebo=0;
public:
  struct vertex {
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 txcds;
  };
  typedef std::pair <gl::Texture &, std::string> mesh_texture;
public:
  std::vector <vertex> vertices;
  std::vector <GLuint> indices;
  std::vector <mesh_texture> textures;
  Mesh(gl::Program &program);
  ~Mesh();
  void Init(std::vector <vertex> &&vertices, std::vector <GLuint> &&indices, std::vector <mesh_texture> &&textures);
  void Draw();
  void Clear();
};
