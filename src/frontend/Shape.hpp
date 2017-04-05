#pragma once

class Shape {
public:
  Shape();
  virtual ~Shape();
  virtual void Init() = 0;
  virtual void Draw() = 0;
  virtual void Clear() = 0;
};
