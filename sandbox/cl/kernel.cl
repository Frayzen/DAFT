__constant float EPSILON = 0.0000001;
__constant int LOOP_THRESHOLD = 30000;

float intersect_triangle(__global const int *triangles, int i, __global const float* vertices, __global const float* normals, float3* ray, float3 cameraPosition){
  if(triangles[9 * i + 3] != -1){
    float3 normal1 = vload3(triangles[9 * i + 3], normals);
    if(dot(*ray, normal1) > 0){
      return -1;
    }
  }
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

bool intersect_bbox(float mint, float3 maxBound, float3 minBound, float3* ry, float3 pos){
  float tmin = -INFINITY;
  float tmax = mint;
  float3 ray = *ry;

  if(ray.x != 0){
    float tx1 = (minBound.x - pos.x) / ray.x;
    float tx2 = (maxBound.x - pos.x) / ray.x;
    tmin = max(tmin, min(tx1, tx2));
    tmax = min(tmax, max(tx1, tx2));
  }
  if(tmin > tmax || tmax < 0){
    return false;
  }
  if(ray.y != 0){
    float ty1 = (minBound.y - pos.y) / ray.y;
    float ty2 = (maxBound.y - pos.y) / ray.y;
    tmin = max(tmin, min(ty1, ty2));
    tmax = min(tmax, max(ty1, ty2));
  }
  if(tmin > tmax || tmax < 0){
    return false;
  }
  if(ray.z != 0){
    float tz1 = (minBound.z - pos.z) / ray.z;
    float tz2 = (maxBound.z - pos.z) / ray.z;
    tmin = max(tmin, min(tz1, tz2));
    tmax = min(tmax, max(tz1, tz2));
  }
  return tmax >= tmin && tmax > 0;
}

__kernel void raytrace(
    __global const float* cameraPosition,
    __global const float* rotationMatrix,
    __global const float* camRays,
    __global const float* vertices,
    __global const float* normals,
    __global const int *triangles,
    int nbTriangle,
    __global const float* minbbox,
    __global const float* maxbbox,
    __global const int2 *children,
    __global unsigned int *result
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
  ray = normalize(ray);

  result[index] = -1;
  
  // for(int i = 0; i < nbTriangle; i++){
  //   int t = intersect_triangle(triangles, i, vertices, normals, &ray, camPos);
  //   if(t > 0){
  //     result[index] = i;
  //     break;
  //   }
  // }

  int stack[35];
  stack[0] = 0;
  int stack_size = 1;
  //dfs
  float mint = INFINITY;
  int countLoop = 0;
  int i;

  while(stack_size > 0){
    countLoop++;
    if(LOOP_THRESHOLD < countLoop){
      printf("loop threshold reached\n");
      break;
    }
    i = stack[stack_size - 1];
    stack_size--;
    if(intersect_bbox(mint, vload3(i, maxbbox), vload3(i, minbbox), &ray, camPos)){
      int2 child = children[i];
      if(child.x < 0){
        int cx = -(child.x+1);
        float t = intersect_triangle(triangles, cx, vertices, normals, &ray, camPos);
        if(t > EPSILON && t < mint){
          mint = t;
          result[index] = cx;
        }
      }else{
        stack[stack_size] = child.x;
        stack_size++;
      }
      if(child.y < 0){
        int cy = -(child.y+1);
        float t = intersect_triangle(triangles, cy, vertices, normals, &ray, camPos);
        if(t > EPSILON && t < mint){
          mint = t;
          result[index] = cy;
        }
      }else{
        stack[stack_size] = child.y;
        stack_size++;
      }
    }
  }
  if(result[index] != -1){
    int t = result[index];
    float3 normal = vload3(triangles[9 * t + 3], normals);
    if(normal.x == 0 && normal.y == 0 && normal.z == 0){
      float3 p1 = vload3(triangles[9 * t], vertices);
      float3 p2 = vload3(triangles[9 * t + 1], vertices);
      float3 p3 = vload3(triangles[9 * t + 2], vertices);
      normal = normalize(cross(p2 - p1, p3 - p1));
    }
    //float3 hit = camPos + mint * ray;
    float diffuse = dot(normal, ray);
    if(diffuse < 0){
      diffuse *= -1;
    }
    unsigned int diffuseValue = 0xFF;
    diffuseValue = diffuseValue * diffuse;
    result[index] = 0x000000FF;
    result[index] |= diffuseValue << 8;
    result[index] |= diffuseValue << 16;
    result[index] |= diffuseValue << 24;
  }else{
    result[index] = 0xFF000000;
  }
}