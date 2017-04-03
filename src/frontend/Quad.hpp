#include "Shape.hpp"

class Quad : public Shape {
protected:
  void AddTriangle(
    const glm::vec3 &a,
    const glm::vec3 &b,
    const glm::vec3 &c,
    size_t index,
    bool is_textured = false
  );
public:
  Quad();
  ~Quad();
  void Init();
  using Shape::Draw;
  using Shape::Clear;
};
