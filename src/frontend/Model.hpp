#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ShaderProgram.hpp"
#include "Mesh.hpp"

class Model {
protected:
  Assimp::Importer importer;
  ShaderProgram &program;
  char directory[255];
  std::vector <Mesh> meshes;
public:
  Model(ShaderProgram &program);
  ~Model();
  void Init(const char *file);
  void ProcessNode(aiNode *node, const aiScene *scene);
  void ProcessMesh(aiMesh *mesh, const aiScene *scene);
  void Draw();
  void Clear();
};