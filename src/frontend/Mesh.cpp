#include "Mesh.hpp"

#include <sstream>

Mesh::Mesh(ShaderProgram &program):
  program(program)
{}

Mesh::~Mesh()
{}

void Mesh::Init(std::vector <vertex> &&verts, std::vector <GLuint> &&inds, std::vector <mesh_texture> &&txrs) {
  vertices = verts, indices = inds, textures = txrs;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex),
               &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               &indices[0], GL_STATIC_DRAW);

  // Vertex Positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), NULL);
  // Vertex Normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, norm));
  // Vertex Texture Coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, txcds));

  glBindVertexArray(0);
}

void Mesh::Draw() {
  /* GLuint diffuse = 1; */
  /* GLuint specular = 1; */
  /* for(GLuint i = 0; i < textures.size(); ++i) { */
  /*   textures[i].first.Bind(i); */
  /*   /1* glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding *1/ */
  /*   // Retrieve texture number (the N in diffuse_textureN) */
  /*   std::stringstream ss; */
  /*   std::string number; */
  /*   std::string name = textures[i].second.type; */
  /*   if(name == "texture_diffuse") */
  /*     ss << diffuse++; // Transfer GLuint to stream */
  /*   else if(name == "texture_specular") */
  /*     ss << specular++; // Transfer GLuint to stream */
  /*   number = ss.str(); */

  /*   glUniform1f(glGetUniformLocation(program.id(), ("material." + name + number).c_str()), i); */
  /*   glBindTexture(GL_TEXTURE_2D, textures[i].id); */
  /* } */
  /* glActiveTexture(GL_TEXTURE0); */

  /* // Draw mesh */
  /* glBindVertexArray(vao); */
  /* glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); */
  /* glBindVertexArray(0); */
}

void Mesh::Clear() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
}
