#pragma once

#include <string>

#include "incgraphics.h"
#include "Storage.hpp"

class Text {
  std::string text;
  size_t color_id;
  GLuint tex = 0;
public:
  Text(std::string text, size_t color_id);
  ~Text();
  void Init();
  void Render();
  void Draw();
  void Clear();
};
