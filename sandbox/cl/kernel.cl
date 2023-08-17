__constant float EPSILON = 0.0000001;
__kernel void raytrace(
    float3 cameraPosition,
    __global const float* rotationMatrix,
    __global const float* camRays,
    __global const float* vertices,
    __global const int *triangles,
    int nbTriangle,
    __global int *result
) {
  int y = get_global_id(0);
  int x = get_global_id(1);

  int index = x + y * get_global_size(1);
  // get ray
  float3 camRay = vload3(index, camRays);

  //rotate ray
  float3 ray = (float3)(dot(camRay, vload3(0, rotationMatrix)),
                        dot(camRay, vload3(1, rotationMatrix)),
                        dot(camRay, vload3(2, rotationMatrix)));

  // for each triangle
  float mint = INFINITY;
  result[index] = -1;
  for (int i = 0; i < nbTriangle; i++) {
    float3 p1 = vload3(triangles[9 * i], vertices);
    float3 p2 = vload3(triangles[9 * i + 1], vertices);
    float3 p3 = vload3(triangles[9 * i + 2], vertices);
    float3 e1 = p2 - p1;
    float3 e2 = p3 - p1;
    float3 h = cross(ray, e2);
    float a = dot(e1, h);
    if (a > -EPSILON && a < EPSILON)
      continue;
    float f = 1.0 / a;
    float3 s = cameraPosition - p1;
    float u = f * dot(s, h);
    if (u < 0.0 || u > 1.0)
      continue;
    float3 q = cross(s, e1);
    float v = f * dot(ray, q);
    if (v < 0.0 || u + v > 1.0)
      continue;
    float t = f * dot(e2, q);
    if (t < EPSILON)
      continue;
    if (t > mint)
      continue;
    // if intersection is in triangle, return the index of the triangle
    result[index] = i;
    mint = t;
  }
}