#include "../../include/architecture/ray.h"

ray create_ray(int width, int height, int x_pix, int y_pix, float FOV, float yaw, float pitch, float pos[3]){
    //float pitch = orientation[1];
    FOV = FOV*M_PI/180;
    float hFOV = FOV/2;
    float pitch_ratio = (float)y_pix/(height-1);
    float yaw_ratio = (float)x_pix/(width-1);
    float deg1 = yaw+hFOV;
    float deg2 = yaw-hFOV;
    float p1[3] = {cos(deg1), 0, sin(deg1)};
    float p2[3] = {cos(deg2), 0, sin(deg2)};
    float flat[3], xz[3], dir[3];
    minus(p2, p1, flat);
    scale(flat, yaw_ratio, flat);
    add(p1, flat, xz);
    deg1 = hFOV;
    float p3[3] = {0, cos(deg1), 0};
    scale(p3, -1, p2);
    minus(p2, p3, flat);
    scale(flat, pitch_ratio, flat);
    float y[3];
    add(p3, flat, y);
    add(xz, y, dir);
    ray ry;
    copy(pos, ry.pos);
    copy(dir, ry.dir);
    return ry;
}

ray* init_rays(int widht, int height, camera* cam){
    ray* rays = calloc(sizeof(ray), widht * height);
    #pragma omp parallel for
    for(int j = 0; j < height; j++){
        #pragma omp parallel for
        for(int i = 0; i < widht; i++)
            rays[i+j*widht] = create_ray(widht, height, i, j, cam->FOV, cam->yaw, cam->pitch, cam->pos);
    }
    
    return rays;
}

void free_rays(ray* rays){
    free(rays);
}

void ray_hit_triangle(ray* r, triangle* tri, float new_mint, float color[3]){
    ray_hit* new_hit = calloc(sizeof(ray_hit), 1);
    new_hit->mint = new_mint;
    new_hit->tri = tri;
    new_hit->m = r->current_mesh;
    for(int i = 0; i < 3; i++)
        new_hit->color[i] = color[i];
    free(r->last_hit);
    r->last_hit = new_hit;
}

