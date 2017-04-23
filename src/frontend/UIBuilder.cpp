#include "UIBuilder.hpp"
#include "Log.hpp"
#include "UserInterface.hpp"

UIBuilder::UIBuilder(UserInterface *ui):
  ui(ui),
  size(100, 100),
  position(ui->width()/2, ui->height()/2)
{}

UIBuilder::~UIBuilder()
{}

void UIBuilder::Resize(float s) {
  Resize(s, s);
}

void UIBuilder::Resize(float x, float y) {
  size = glm::vec2(size.x * x, size.y * y);
}

void UIBuilder::SetSize(float s) {
  SetSize(s, s);
}

void UIBuilder::SetSize(float x, float y) {
  size = glm::vec2(x, y);
}

void UIBuilder::Move(float x, float y) {
  SetPosition(x + position.x, y + position.y);
}

void UIBuilder::SetPosition(float x, float y) {
  position = glm::vec2(x, y);
}
