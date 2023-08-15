__constant float EPSILON = 0.0000001;
__kernel void raytrace(
  float3 cameraPosition,
  float3 cameraRotation,
  __global const float3 *camRays,
  __global const float3 *vertices,
  __global const int3 *triangles,
  int nbTriangle,
  __global int*result
  ) {
  int y = get_global_id(0);
  int x = get_global_id(1);
  
  int index = x + y * get_global_size(1);
  //get ray
  float3 camRay = camRays[index];
  //rotate ray
  float3 ray;
  ray.x = camRay.x * cos(cameraRotation.y) + camRay.z * sin(cameraRotation.y);
  ray.y = camRay.y;
  ray.z = -camRay.x * sin(cameraRotation.y) + camRay.z * cos(cameraRotation.y);
  //for each triangle
  float mint = INFINITY;
  result[index] = -1;
  for(int i = 0; i < nbTriangle; i++){
    int3 triangle = triangles[i];
    float3 p1 = vertices[triangle.x];
    float3 p2 = vertices[triangle.y];
    float3 p3 = vertices[triangle.z];
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
    if(t > mint)
      continue;
    //if intersection is in triangle, return the index of the triangle
    result[index] = i;
    mint = t;
  }
}