#include "Sphere.hpp"
#include "Camera.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

#include <omp.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

const size_t Sphere::DIM = 100;
const size_t Sphere::SIZE = DIM*2 * DIM*2;
Sphere::Sphere():
  Shape()
{}

Sphere::~Sphere()
{}

glm::vec3 point_on_sphere(double dyx, double dzx) {
  //sin(dyx) is a radius of unitary zx circle
  return glm::vec3(
    /*x*/sin(dyx)*cos(dzx),
    /*y*/cos(dyx),
    /*z*/sin(dyx)*sin(dzx)
  );
}

void Sphere::Init() {
  vao.Init();
  vao.Bind();

  txcoords = new GLfloat[SIZE * 6];
  ASSERT(txcoords != NULL);
  vertices = new GLfloat[SIZE * 9];
  ASSERT(vertices != NULL);

  InitBuffers();

  for(size_t i = 0; i < SIZE; ++i) {
    GLfloat *v = &vertices[i*9];
    Logger::Say("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
           v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8]);
  }

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

void Sphere::InitBuffers() {
  const double step = M_PI / double(DIM);
  #pragma omp parallel for num_threads(8)
  for(size_t i = 0; i < DIM; ++i) {
    const double dyx = double(i) * step;
    for(size_t j = 0; j < DIM*2; ++j) {
      int index = 2 * (i * DIM * 2 + j);
      const double dzx = double(j) * step;
      SetTexcoords(index);
      SetVertices(
        point_on_sphere(dyx, dzx),
        point_on_sphere(dyx + step, dzx + step),
        point_on_sphere(dyx + step, dzx),
      index);
      ++index;
      SetTexcoords(index);
      SetVertices(
        point_on_sphere(dyx, dzx),
        point_on_sphere(dyx, dzx + step),
        point_on_sphere(dyx + step, dzx + step),
      index);
    }
  }
}

void Sphere::SetTexcoords(size_t index) {
  ASSERT(index < SIZE);
  GLfloat *buffer = &txcoords[index * 6];
  size_t
    y = DIM - 1 - (index/2) / (2 * DIM),
    x = (index/2) % (2 * DIM);
  float xstep = 0.5f / float(DIM);
  float tx0 = float(x) / float(2 * DIM);
  float tx1 = tx0 + xstep;
  float ystep = 1.0f / float(DIM);
  float ty0 = float(y) / float(DIM);
  float ty1 = ty0 + ystep;
  if(index & 1) {
    buffer[0] = tx0, buffer[1] = ty1,
    buffer[2] = tx1, buffer[3] = ty1,
    buffer[4] = tx1, buffer[5] = ty0;
  } else {
    buffer[0] = tx0, buffer[1] = ty1,
    buffer[2] = tx1, buffer[3] = ty0,
    buffer[4] = tx0, buffer[5] = ty0;
  }
  Logger::Say("%.2f,%.2f\n", buffer[0], buffer[1]);
  Logger::Say("%.2f,%.2f\n", buffer[2], buffer[3]);
  Logger::Say("%.2f,%.2f\n", buffer[4], buffer[5]);
}

void Sphere::SetVertices(const glm::vec3 &&a, const glm::vec3 &&b, const glm::vec3 &&c, size_t index) {
  ASSERT(index < SIZE);
  GLfloat *buffer = &vertices[index * 9];
  memcpy(buffer, glm::value_ptr(a), sizeof(GLfloat) * 3);
  memcpy(buffer + 3, glm::value_ptr(b), sizeof(GLfloat) * 3);
  memcpy(buffer + 6, glm::value_ptr(c), sizeof(GLfloat) * 3);
  Logger::Say("adding triangle_strip\n");
  Logger::Say("%.2f,%.2f,%.2f\n", buffer[0], buffer[1], buffer[2]);
  Logger::Say("%.2f,%.2f,%.2f\n", buffer[3], buffer[4], buffer[5]);
  Logger::Say("%.2f,%.2f,%.2f\n", buffer[6], buffer[7], buffer[8]);
}

void Sphere::Draw() {
  vao.Bind();
  glDrawArrays(GL_TRIANGLES, 0, SIZE * 3); GLERROR
}

void Sphere::Clear() {
  vert.Clear();
  tex.Clear();
  vao.Clear();
}
