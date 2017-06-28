#include "Sphere.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

#include "Camera.hpp"
#include "Computation.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

const size_t Sphere::DIM = 300;
const size_t Sphere::SIZE = DIM*2 * DIM*2;
Sphere::Sphere():
  Shape()
{}

Sphere::~Sphere()
{}

glm::vec3 point_on_sphere(double dyx, double dzx) {
  //sin(dyx) is a radius of unitary zx circle
  return glm::vec3(
    sin(dyx)*cos(dzx),
    cos(dyx),
    sin(dyx)*sin(dzx)
  );
}

using namespace compute;
void Sphere::Init() {
  vao.Init();
  vao.Bind();

  txcoords = new GLfloat[SIZE * 6];
  ASSERT(txcoords != NULL);
  vertices = new GLfloat[SIZE * 9];
  ASSERT(vertices != NULL);

  {
    Computation compute("sphere.cl", "sphere");
    compute.init();
    {
      auto tex = compute.make_membuf<cl_float, CL_MEM_READ_ONLY>(txcoords, SIZE * 6);
      auto vrt = compute.make_membuf<cl_float, CL_MEM_READ_ONLY>(vertices, SIZE * 9);
      compute.attach(tex);
      compute.attach(vrt);
      compute.attach(cl_int(DIM));
      compute.execute(SIZE);
      tex.get_data();
      vrt.get_data();
    }
    compute.clear();
  }

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

void Sphere::Draw() {
  vao.Bind();
  glDrawArrays(GL_TRIANGLES, 0, SIZE * 3); GLERROR
}

void Sphere::Clear() {
  vert.Clear();
  tex.Clear();
  vao.Clear();
}
