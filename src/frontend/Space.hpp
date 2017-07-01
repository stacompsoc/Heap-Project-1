#pragma once

#include <vector>

#include "Camera.hpp"
#include "MultiObject.hpp"
#include "ShaderProgram.hpp"
#include "Scenerao.hpp"
#include "MultiObjectConstructor.hpp"

class Space {
protected:
  friend class Scenerao;
  gl::ShaderProgram
    planetProgram,
    skeletonProgram;
  Scenerao
    mainScenerao;
  MultiObjectConstructor
    constructor;
  Camera
    cam;
  std::vector <MultiObject>
    spaceObjects;
  static Space *instance;
  Space();
  ~Space();
public:
  size_t AddMultiObject();
  size_t AddObject(Object &&object);
  void Init();
  void Draw();
  void Clear();
  static Space *inst();
  static Camera *Cam();
  static void Setup();
  static void Cleanup();
};
