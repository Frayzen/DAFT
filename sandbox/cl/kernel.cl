__constant float EPSILON = 0.0000001;
__constant int LOOP_THRESHOLD = 30;

int test_triangle(__global const int *triangles, int i, __global const float* vertices, float3* ray, float3 cameraPosition){
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
  if (t < EPSILON)
    return -1;
  return t;
}

bool intersect_bbox(float3 max, float3 min, float3 ray){
  
}

__kernel void raytrace(
    float3 cameraPosition,
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

  //rotate ray
  float3 ray = (float3)(dot(camRay, vload3(0, rotationMatrix)),
                        dot(camRay, vload3(1, rotationMatrix)),
                        dot(camRay, vload3(2, rotationMatrix)));

  result[index] = -1;
  int depth = ceil(log2((float) nbTriangle));
  int stack[35];
  stack[0] = 0;
  int stack_size = 1;
  //dfs
  int mint = INFINITY;
  int countLoop = 0;
  int i;

  while(stack_size > 0){
    countLoop++;
    if(LOOP_THRESHOLD < countLoop){
                //print stack
      printf("stack (size %d): %d %d %d %d...", stack_size, stack[0], stack[1], stack[2], stack[3]);
      printf("loop threshold reached\n");
      break;
    }
    i = stack[stack_size - 1];
    stack_size--;
    if(intersect_bbox(vload3(i, maxbbox), vload3(i, minbbox), ray)){

      int2 child = children[i];
      if(child.x < 0){
        int cx = -(child.x+1);
        int t = test_triangle(triangles, -cx, vertices, &ray, cameraPosition);
        if(t > 0 && t < mint){
          mint = t;
          result[index] = cx;
        }
      }else{
        stack[stack_size] = child.x;
        stack_size++;
      }
      if(child.y < 0){
        int cy = -(child.y+1);
        int t = test_triangle(triangles, -cy, vertices, &ray, cameraPosition);
        if(t > 0 && t < mint){
          mint = t;
          result[index] = cy;
        }
      }else{
        stack[stack_size] = child.y;
        stack_size++;
      }
    }
  }
}