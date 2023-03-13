#include "../../include/architecture/ray.h"

ray* init_rays(int widht, int height){
    ray* rays = calloc(sizeof(ray), widht * height);
    return rays;
}

void free_rays(ray* rays){
    free(rays);
}

