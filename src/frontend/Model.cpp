#include "Model.hpp"
#include "Log.hpp"

#include <libgen.h>

Model::Model(ShaderProgram &program):
  program(program)
{}

Model::~Model()
{}

void Model::Init(const char *file) {
  const aiScene *scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);
  if(scene == NULL || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == NULL) {
    gl_log("error: %s\n", importer.GetErrorString());
  }
  /* directory = dirname(file); */
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
  /* for(GLuint i = 0; i < node->mNumMeshes; ++i) { */
  /*   aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; */
  /*   meshes.push_back(ProcessMesh(mesh, scene)); */
  /* } */
  /* for(GLuint i = 0; i < node->mNumChildren; ++i) { */
  /*   ProcessNode(node->mChildren[i], scene); */
  /* } */
}

void Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
}

void Model::Draw() {
  for(auto &mesh : meshes)
    mesh.Draw();
}

void Model::Clear() {
}
