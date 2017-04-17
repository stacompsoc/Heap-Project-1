#include "UserInterface.hpp"
#include "Log.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

UserInterface::UserInterface(Screen *screen):
  screen(screen),
  quadProgram({"pquad.vert", "pquad.frag"}),
  textProgram({"ptext.vert", "ptext.frag"}),
  /* label("Push"), */
  u_proj("projection")
{}

UserInterface::~UserInterface()
{}

size_t UserInterface::width() {
  return screen->width();
}

size_t UserInterface::height() {
  return screen->height();
}

void UserInterface::AddObject(Object &&object) {
  uiObjects.push_back(object);
  uiObjects.back().Init();
}

void UserInterface::AddQuad(size_t texture_id, glm::vec2 &&pos, glm::vec2 &&scale) {
  AddObject(
    Object(
      Storage::QUAD, texture_id, quadProgram,
      glm::vec3(pos.x, pos.y, -0.5),
      glm::vec3(scale.x, scale.y, 0),
      0, 0
    )
  );
}

void UserInterface::AddText(TextObject &&textobj) {
  uiTexts.push_back(textobj);
  uiTexts.back().Init();
}

void UserInterface::Init() {
  size_t ARIAL = Storage::AddFont("fonts/Arial.ttf");
  quadProgram.Init({"vposition", "vtexcoords"});
  textProgram.Init({"vertex"});
  BCKGR = Storage::AddTexture("textures/menubackground.jpg");
  BTN = Storage::AddTexture("textures/button.png");
  BTNSEL = Storage::AddTexture("textures/button_sel.png");
  projection_matrix = glm::ortho(0.0f, float(width()), 0.0f, float(height()));
  AddQuad(BCKGR, glm::vec2(width()/2, height()/2), glm::vec2(width()/2, height()/2));
  AddText(
    TextObject(
      "Amazing space picture", ARIAL, textProgram,
      glm::vec2(width()/2, height()/2),
      glm::vec3(1, 1, 1),
      1.0f
    )
  );
}

void UserInterface::Draw() {
  glEnable(GL_BLEND); GLERROR
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); GLERROR

  quadProgram.Use();
  u_proj.set_id(quadProgram.id());
  u_proj.set_data(projection_matrix);
  textProgram.Use();
  u_proj.set_id(textProgram.id());
  u_proj.set_data(projection_matrix);

  for(auto &obj : uiObjects)
    obj.Draw();
  for(auto &tobj : uiTexts)
    tobj.Draw();
  ShaderProgram::Unuse();
}

void UserInterface::Clear() {
  for(auto &obj : uiObjects)
    obj.Clear();
  for(auto &tobj : uiTexts)
    tobj.Clear();
}

UserInterface *UserInterface::inst() {
  return instance;
}

UserInterface *UserInterface::instance = NULL;
void UserInterface::Setup(Screen *screen) {
  ASSERT(instance == NULL);
  instance = new UserInterface(screen);
  instance->Init();
}

void UserInterface::CleanUp() {
  ASSERT(instance != NULL);
  instance->Clear();
  delete instance;
  instance = NULL;
}
