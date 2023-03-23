#include "../../include/architecture/ray.h"

ray* init_rays(int widht, int height){
    ray* rays = calloc(sizeof(ray), widht * height);
    return rays;
}

void free_rays(ray* rays){
    free(rays);
}

void ray_hit(ray* r, triangle* tri, float new_mint, float color[3]){
    ray_hit* new_hit = calloc(sizeof(ray_hit), 1);
    new_hit->mint = new_mint;
    new_hit->tri = tri;
    new_hit->m = r->current_mesh;
    for(int i = 0; i < 3; i++)
        new_mint->color[i] = color[i];
    free(r->last_hit);
    r->last_hit = r;
}