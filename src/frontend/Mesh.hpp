#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "incgraphics.h"

#include "ShaderProgram.hpp"
#include "Texture.hpp"

class Mesh  {
private:
  ShaderProgram program;
  GLuint vao=0, vbo=0, ebo=0;
  struct vertex {
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 txcds;
  };
  typedef std::pair <Texture &, std::string> mesh_texture;
public:
  std::vector <vertex> vertices;
  std::vector <GLuint> indices;
  std::vector <mesh_texture> textures;
  Mesh(ShaderProgram &program);
  ~Mesh();
  void Init(std::vector <vertex> &&vertices, std::vector <GLuint> &&indices, std::vector <mesh_texture> &&textures);
  void Draw();
  void Clear();
};
