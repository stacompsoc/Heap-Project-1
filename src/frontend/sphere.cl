__local float3 point_on_sphere(const float dyx, const float dzx) {
  return (float3)(
    sin(dyx) * cos(dzx),
    cos(dyx),
    sin(dyx) * sin(dzx)
  );
}

__local void set_texcoords(__global float *texcoords, const int dim, const int index) {
  float dimf = dim;
  int IF = index & 1;

  {
    const int offset = index * 6;

    const float tx0 = (index/2) % (2 * dim) / (2. * dimf);
    const float tx1 = tx0 + (0.5 / dimf);

    const float ty0 = (dim - 1 - (index/2) / (2 * dim)) / dimf;
    const float ty1 = ty0 + (1. / dimf);

    float3 a = (float3)(tx0, ty1, tx1);
    float3 b = (float3)(ty0 + (1./dimf)*IF, tx0 + (0.5/dimf)*IF, ty0);

    texcoords[offset+0] = a.x;
    texcoords[offset+1] = a.y;
    texcoords[offset+2] = a.z;

    texcoords[offset+3] = b.x;
    texcoords[offset+4] = b.y;
    texcoords[offset+5] = b.z;
  }
}

__local void set_vertices(__global float *vertices, const int dim, const int index) {
  float dimf = dim;
  int IF = index & 1;

  {
    const int offset = index * 9;

    const float step = 3.14159265359 / dimf;
    int ij = index / 2;
    const float dyx = (float)(ij / (dim * 2)) * step;
    const float dzx = (float)(ij % (dim * 2)) * step;

    float3 a = point_on_sphere(dyx, dzx);
    float3 b = point_on_sphere(dyx + (!IF)*step, dzx + step);
    float3 c = point_on_sphere(dyx + step, dzx + IF*step);

    vertices[offset+0] = a.x;
    vertices[offset+1] = a.y;
    vertices[offset+2] = a.z;

    vertices[offset+3] = b.x;
    vertices[offset+4] = b.y;
    vertices[offset+5] = b.z;

    vertices[offset+6] = c.x;
    vertices[offset+7] = c.y;
    vertices[offset+8] = c.z;
  }
}

__kernel void sphere(__global float *texcoords, __global float *vertices, const int dim) {
  int index = get_global_id(0);

  set_texcoords(texcoords, dim, index);
  set_vertices(vertices, dim, index);
}
