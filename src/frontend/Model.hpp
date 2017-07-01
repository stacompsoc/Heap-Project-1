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
  gl::ShaderProgram &program;
  char directory[255];
  std::vector <Mesh> meshes;
public:
  Model(gl::ShaderProgram &program);
  ~Model();
  void Init(const char *file);
  void ProcessNode(aiNode *node, const aiScene *scene);
  Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
  void LoadMaterialTexture(aiMaterial *material, aiTextureType type, std::string type_name);
  void Draw();
  void Clear();
};
