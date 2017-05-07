#include "Model.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

#include <libgen.h>

Model::Model(ShaderProgram &program):
  program(program)
{}

Model::~Model()
{}

void Model::Init(const char *file) {
  const aiScene *scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);
  if(scene == NULL || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == NULL) {
    Logger::Error("%s\n", importer.GetErrorString());
  }
  /* directory = dirname(file); */
  ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
  for(GLuint i = 0; i < node->mNumMeshes; ++i) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
  /*   meshes.push_back(ProcessMesh(mesh, scene)); */
  }
  for(GLuint i = 0; i < node->mNumChildren; ++i) {
    ProcessNode(node->mChildren[i], scene);
  }
}

/* Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) { */
  /* std::vector <Mesh::vertex> vertices; */
  /* std::vector <GLuint> indices; */
  /* std::vector <Texture> textures; */
  /* for(GLuint i = 0; i < mesh->mNumVertices; ++i) { */
  /*   Mesh::vertex vertex; */
  /*   glm::vec3 vec(mesh->mNumVertices[i].x, mesh->mNumVertices[i].y, mesh->mNumVertices[i].z); */
  /*   vertex.pos = vec; */
  /*   vec = glm::vec3(mesh->mNumNormals[i].x, mesh->mNumNormals[i].y, mesh->mNumNormals[i].z); */
  /*   vertex.norm = vec; */
  /*   if(mesh->mTextureCoords[0]) { */
  /*     vertex.txcds.x = mesh->mTextureCoords[0][i].x; */
  /*     vertex.txcds.y = mesh->mTextureCoords[0][i].y; */
  /*   } else { */
  /*     vertex.txcds = glm::vec2(0.0f, 0.0f); */
  /*   } */
  /*   vertices.push_back(vertex); */
  /* } */
  /* for(GLuint i = 0; i < mesh->mNumFaces; ++i) { */
  /*   aiFace = mesh->mFaces[i]; */
  /*   for(GLuint j = 0; j < face.mNumIndices; ++j) { */
  /*     indices.push_back(face.mIndices[j]); */
  /*   } */
  /* } */
  /* if(mesh->mMaterialIndex >= 0) { */
  /*   aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex]; */
  /*   // diffuse maps */
  /*   std::vector <Texture> diffuse_maps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse"); */
  /*   textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end()); */
  /*   std::vector <Texture> specular_maps = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular"); */
  /*   textures.insert(textures.end(), specular_maps.begin(), specular_maps.end()); */
  /* } */
  /* Mesh ret; ret.Init(vertices, indices, mesh_texture); return ret; */
/* } */

/* std::vector <Texture> Model::LoadMaterialTexture(aiMaterial *material, aiTextureType type, std::string type_name) { */
  /* std::vector <Texture> textures; */
  /* for(GLuint i = 0; i < material->GetTextureCount(type); ++i) { */
  /*   aiString str; */
  /*   material->GetTexture(type, i, &str); */
  /*   GLboolean skip = false; */
  /*   for(GLuint j = 0; j < textures_loaded.size(); ++j) { */
  /*     // TODO */
  /*   } */
  /* } */
/* } */

void Model::Draw() {
  for(auto &mesh : meshes)
    mesh.Draw();
}

void Model::Clear() {
}
