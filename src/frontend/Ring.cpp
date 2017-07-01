#include "Ring.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

#include <omp.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

template <int N> const size_t Ring<N>::DIM = N*100;
template <int N> const size_t Ring<N>::SIZE = DIM * 2;

template <int N>
Ring<N>::Ring():
  Shape()
{}

template <int N>
Ring<N>::~Ring()
{}

glm::vec3 point_on_circle(float angle) {
  return glm::vec3(cos(angle), 0, sin(angle));
}

template <int N>
void Ring<N>::Init() {
  vao.Init();
  vao.Bind();

  txcoords = new GLfloat[SIZE * 6];
  ASSERT(txcoords != NULL);
  vertices = new GLfloat[SIZE * 9];
  ASSERT(vertices != NULL);

  InitBuffers();

  vert.Init(GL_ARRAY_BUFFER);
  vert.Bind();
  glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(GLfloat) * 9, vertices, GL_STREAM_DRAW); GLERROR

  tex.Init(GL_ARRAY_BUFFER);
  tex.Bind();
  glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(GLfloat) * 6, txcoords, GL_STREAM_DRAW); GLERROR

  ASSERT(vertices != NULL);
  delete vertices;
  ASSERT(txcoords != NULL);
  delete txcoords;

  glEnableVertexAttribArray(0); GLERROR
  vert.Bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR

  glEnableVertexAttribArray(1); GLERROR
  tex.Bind();
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR

  glVertexAttribDivisor(0, 0); GLERROR
  glVertexAttribDivisor(1, 0); GLERROR
}

template <int N>
void Ring<N>::InitBuffers() {
  const static float ir = float(10-N) / 10;
  const double step = float(M_PI*2) / DIM;
  #pragma omp parallel for num_threads(8)
  for(size_t i = 0; i < DIM; ++i) {
    const double angle = double(i) * step;
    size_t index = i * 2;
    glm::vec3
      &&a = point_on_circle(angle),
      &&b = point_on_circle(angle + step),
      &&c = a * ir;
    SetTexcoords(index);
    SetVertices(a, b, c, index), ++index;
    a = b * ir;
    SetTexcoords(index);
    SetVertices(c, b, a, index), ++index;
  }
}

template <int N>
void Ring<N>::SetTexcoords(int index) {
  ASSERT(index < SIZE);
  size_t x = index / 2;
  ASSERT(x < DIM);
  float xstep = 1. / DIM;
  float tx0 = float(x) / DIM, tx1 = tx0 + xstep;
  GLfloat *buffer = &txcoords[index * 6];
  if(index & 1) {
    buffer[0] = tx1, buffer[1] = 1,
    buffer[2] = tx0, buffer[3] = 0,
    buffer[4] = tx0, buffer[5] = 1;
  } else {
    buffer[0] = tx1, buffer[1] = 0,
    buffer[2] = tx0, buffer[3] = 0,
    buffer[4] = tx1, buffer[5] = 1;
  }
  /* Logger::Say("%.2f,%.2f\n", buffer[0], buffer[1]); */
  /* Logger::Say("%.2f,%.2f\n", buffer[2], buffer[3]); */
  /* Logger::Say("%.2f,%.2f\n", buffer[4], buffer[5]); */
}

template <int N>
void Ring<N>::SetVertices(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, size_t index) {
  ASSERT(index < SIZE);
  GLfloat *buffer = &vertices[index * 9];
  memcpy(buffer, glm::value_ptr(a), sizeof(GLfloat) * 3);
  memcpy(buffer + 3, glm::value_ptr(b), sizeof(GLfloat) * 3);
  memcpy(buffer + 6, glm::value_ptr(c), sizeof(GLfloat) * 3);
  /* Logger::Say("adding triangle_strip\n"); */
  /* Logger::Say("%.2f,%.2f,%.2f\n", a.x,a.y,a.z); */
  /* Logger::Say("%.2f,%.2f,%.2f\n", b.x,b.y,b.z); */
  /* Logger::Say("%.2f,%.2f,%.2f\n", c.x,c.y,c.z); */
}

template <int N>
void Ring<N>::Draw() {
  vao.Bind();
  glDrawArrays(GL_TRIANGLES, 0, SIZE * 3); GLERROR
}

template <int N>
void Ring<N>::Clear() {
  vert.Clear();
  tex.Clear();
  vao.Clear();
}

template class Ring<1>;
template class Ring<2>;
template class Ring<3>;
template class Ring<7>;
template class Ring<8>;
