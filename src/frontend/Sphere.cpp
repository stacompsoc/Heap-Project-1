#include "Sphere.hpp"
#include "Camera.hpp"
#include "Log.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

const size_t Sphere::DIM = 50;
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

  /* for(size_t i = 0; i < SIZE; ++i) { */
  /*   GLfloat *v = &vertices[i*9]; */
  /*   printf("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", */
  /*          v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8]); */
  /* } */

  glGenBuffers(1, &vert_vbo); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, vert_vbo); GLERROR
  glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(GLfloat) * 9, vertices, GL_STREAM_DRAW); GLERROR

  glGenBuffers(1, &tex_vbo); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, tex_vbo); GLERROR
  glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(GLfloat) * 6, txcoords, GL_STREAM_DRAW); GLERROR

  ASSERT(vertices != NULL);
  delete vertices;
  ASSERT(txcoords != NULL);
  delete txcoords;

  glEnableVertexAttribArray(0); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, vert_vbo); GLERROR
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR

  glEnableVertexAttribArray(1); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, tex_vbo); GLERROR
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR

  glVertexAttribDivisor(0, 0); GLERROR
  glVertexAttribDivisor(1, 0); GLERROR
}

void Sphere::InitBuffers() {
  int index = 0;
  const double step = M_PI / double(DIM);
  /* float rx = 1.0 - float(rand() % 10) / 10.; */
  /* float ry = 1.0 - float(rand() % 10) / 10.; */
  /* float rz = 1.0 - float(rand() % 10) / 10.; */
  /* printf("%.2f,%.2f,%.2f\n", rx,ry,rz); */
  /* glm::vec3 p(rx, ry, rz); */
  #define p
  for(size_t i = 0; i < DIM; ++i) {
    double dyx = double(i) * step;
    for(size_t j = 0; j < DIM*2; ++j) {
      double dzx = double(j) * step;
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
      ++index;
    }
  }
  #undef p
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
  gl_log("%.2f,%.2f\n", buffer[0], buffer[1]);
  gl_log("%.2f,%.2f\n", buffer[2], buffer[3]);
  gl_log("%.2f,%.2f\n", buffer[4], buffer[5]);
}

void Sphere::SetVertices(const glm::vec3 &&a, const glm::vec3 &&b, const glm::vec3 &&c, size_t index) {
  ASSERT(index < SIZE);
  GLfloat *buffer = &vertices[index * 9];
  memcpy(buffer, glm::value_ptr(a), sizeof(GLfloat) * 3);
  memcpy(buffer + 3, glm::value_ptr(b), sizeof(GLfloat) * 3);
  memcpy(buffer + 6, glm::value_ptr(c), sizeof(GLfloat) * 3);
  gl_log("adding triangle_strip\n");
  gl_log("%.2f,%.2f,%.2f\n", buffer[0], buffer[1], buffer[2]);
  gl_log("%.2f,%.2f,%.2f\n", buffer[3], buffer[4], buffer[5]);
  gl_log("%.2f,%.2f,%.2f\n", buffer[6], buffer[7], buffer[8]);
}

void Sphere::Draw() {
  vao.Bind();
  glDrawArrays(GL_TRIANGLES, 0, SIZE * 3); GLERROR
}

void Sphere::Clear() {
  glDeleteBuffers(1, &vert_vbo); GLERROR
  glDeleteBuffers(1, &tex_vbo); GLERROR
  vao.Clear();
}
