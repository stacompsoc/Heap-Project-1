__local float3 point_on_sphere(const float dyx, const float dzx) {
  return (float3)(
    sin(dyx) * cos(dzx),
    cos(dyx),
    sin(dyx) * sin(dzx)
  );
}

__local void set_texcoords(__global float2 *texcoords, const int dim, const int index) {
  float dimf = dim;
  int IF = index & 1;

  {
    const int offset = index * 3;

    const float tx0 = (index/2) % (2 * dim) / (2. * dimf);
    const float txstep = .5/dimf;

    const float ty0 = (dim - 1 - (index/2) / (2 * dim)) / dimf;
    const float tystep = 1./dimf;

    texcoords[offset+0] = (tx0, ty0 + tystep);
    texcoords[offset+1] = (tx0 + txstep, ty0 + tystep*IF);
    texcoords[offset+2] = (tx0 + txstep*IF, ty0);
  }
}

__local void set_vertices(__global float *vertices, const int dim, const int index) {
  float dimf = dim;
  int IF = index & 1;

  {
    const float step = 3.14159265359 / dimf;
    const float dyx = (float)((index/2) / (dim * 2)) * step;
    const float dzx = (float)((index/2) % (dim * 2)) * step;

    const int offset = index * 9;
    vstore3(point_on_sphere(dyx, dzx), 0, &vertices[offset]);
    vstore3(point_on_sphere(dyx + (!IF)*step, dzx + step), 1, &vertices[offset]);
    vstore3(point_on_sphere(dyx + step, dzx + IF*step), 2, &vertices[offset]);
  }
}

__kernel void sphere(__global float2 *texcoords, __global float *vertices, const int dim) {
  int index = get_global_id(0);
  set_texcoords(texcoords, dim, index);
  set_vertices(vertices, dim, index);
}
