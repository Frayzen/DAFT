
__kernel void raytrace(
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
  float3 ray = camRays[index];
  //for each triangle
  float mint = INFINITY;
  for(int i = 0; i < nbTriangle; i++){
    int3 triangle = triangles[i];
    float3 p1 = vertices[triangle.x];
    float3 p2 = vertices[triangle.y];
    float3 p3 = vertices[triangle.z];
    //get normal
    float3 normal = cross(p2 - p1, p3 - p1);
    //get distance
    float distance = dot(normal, p1);
    //get intersection
    float t = (distance - dot(normal, ray)) / dot(normal, cameraRotation);
    if(t < 0 || t > mint){
      continue;
    }
    float3 intersection = ray * t;
    //check if intersection is in triangle
    float3 edge0 = p2 - p1;
    float3 vp0 = intersection - p1;
    float3 c = cross(edge0, vp0);
    if(dot(normal, c) < 0){
      continue;
    }
    float3 edge1 = p3 - p2;
    float3 vp1 = intersection - p2;
    c = cross(edge1, vp1);
    if(dot(normal, c) < 0){
      continue;
    }
    float3 edge2 = p1 - p3;
    float3 vp2 = intersection - p3;
    c = cross(edge2, vp2);
    if(dot(normal, c) < 0){
      continue;
    }
    //if intersection is in triangle, return the index of the triangle
    result[index] = i+1;
    mint = t;
  }
}