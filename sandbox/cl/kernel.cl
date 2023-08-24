__constant float EPSILON = 0.0000001;
__constant int LOOP_THRESHOLD = 30000;

int intersect_triangle(__global const int *triangles, int i, __global const float* vertices, float3* ray, float3 cameraPosition){
  float3 p1 = vload3(triangles[9 * i], vertices);
  float3 p2 = vload3(triangles[9 * i + 1], vertices);
  float3 p3 = vload3(triangles[9 * i + 2], vertices);
  float3 e1 = p2 - p1;
  float3 e2 = p3 - p1;
  float3 h = cross(*ray, e2);
  float a = dot(e1, h);
  if (a > -EPSILON && a < EPSILON)
    return -1;
  float f = 1.0 / a;
  float3 s = cameraPosition - p1;
  float u = f * dot(s, h);
  if (u < 0.0 || u > 1.0)
    return -1;
  float3 q = cross(s, e1);
  float v = f * dot(*ray, q);
  if (v < 0.0 || u + v > 1.0)
    return -1;
  float t = f * dot(e2, q);
  return t;
}

bool intersect_bbox(float3 maxBound, float3 minBound, float3 ray, float3 pos){
  float tmin = -INFINITY;
  float tmax = INFINITY;
  if(ray.x != 0){
    float tx1 = (minBound.x - pos.x) / ray.x;
    float tx2 = (maxBound.x - pos.x) / ray.x;
    tmin = max(tmin, min(tx1, tx2));
    tmax = min(tmax, max(tx1, tx2));
  }
  if(tmax < tmin)
    return false;
  if(ray.y != 0){
    float ty1 = (minBound.y - pos.y) / ray.y;
    float ty2 = (maxBound.y - pos.y) / ray.y;
    tmin = max(tmin, min(ty1, ty2));
    tmax = min(tmax, max(ty1, ty2));
  }
  if(tmax < tmin)
    return false;
  if(ray.z != 0){
    float tz1 = (minBound.z - pos.z) / ray.z;
    float tz2 = (maxBound.z - pos.z) / ray.z;
    tmin = max(tmin, min(tz1, tz2));
    tmax = min(tmax, max(tz1, tz2));
  }
  return tmax >= tmin;
}

__kernel void raytrace(
    __global const float* cameraPosition,
    __global const float* rotationMatrix,
    __global const float* camRays,
    __global const float* vertices,
    __global const int *triangles,
    int nbTriangle,
    __global const float* minbbox,
    __global const float* maxbbox,
    __global const int2 *children,
    __global int *result
) {
  int y = get_global_id(0);
  int x = get_global_id(1);

  int index = x + y * get_global_size(1);
  // get ray
  float3 camRay = vload3(index, camRays);
  float3 camPos = vload3(0, cameraPosition);

  // rotate ray
  float3 ray = (float3)(
    dot(camRay, vload3(0, rotationMatrix)),
    dot(camRay, vload3(1, rotationMatrix)),
    dot(camRay, vload3(2, rotationMatrix))
  );

  result[index] = -1;
  
  for(int i = 0; i < nbTriangle; i++){
    int t = intersect_triangle(triangles, i, vertices, &ray, camPos);
    if(t > 0){
      result[index] = i;
      break;
    }
  }

  // int stack[35];
  // stack[0] = 0;
  // int stack_size = 1;
  // //dfs
  // int mint = INFINITY;
  // int countLoop = 0;
  // int i;

  // while(stack_size > 0){
  //   countLoop++;
  //   if(LOOP_THRESHOLD < countLoop){
  //     printf("loop threshold reached\n");
  //     break;
  //   }
  //   i = stack[stack_size - 1];
  //   stack_size--;
  //   if(intersect_bbox(vload3(i, maxbbox), vload3(i, minbbox), ray, camPos)){
  //     int2 child = children[i];
  //     if(child.x < 0){
  //       int cx = -(child.x+1);
  //       int t = intersect_triangle(triangles, cx, vertices, &ray, camPos);
  //       if(t > 0 && t < mint){
  //         mint = t;
  //         result[index] = cx;
  //       }
  //     }else{
  //       stack[stack_size] = child.x;
  //       stack_size++;
  //     }
  //     if(child.y < 0){
  //       int cy = -(child.y+1);
  //       int t = intersect_triangle(triangles, cy, vertices, &ray, camPos);
  //       if(t > 0 && t < mint){
  //         mint = t;
  //         result[index] = cy;
  //       }
  //     }else{
  //       stack[stack_size] = child.y;
  //       stack_size++;
  //     }
  //   }
  // }
}