#pragma once

class Space;

class Scenerao {
protected:
  Space *space;
public:
  Scenerao(Space *space);
  ~Scenerao();
  void Init();
  void Next();
  void Clear();
};
