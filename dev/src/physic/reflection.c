#include "../../include/physic/reflection.h"

void reflection(raycast_param* rcp){
    ray* ry = rcp->r;
    float d_n = dotProduct(ry->last_hit->normal, ry->dir);
    float new_dir[3];
    scale(ry->last_hit->normal, d_n*2, new_dir);
    minus(ry->dir, new_dir, new_dir);
    ray * new_ray = malloc(sizeof(ray));
    normalize(ry->dir, new_ray->pos);
    scale(new_ray->pos, ry->last_hit->mint, new_ray->pos);
    normalize(new_dir, new_ray->dir);
    float reflected = ry->last_hit->reflectivity;
    new_ray->last_hit = NULL;
    
    raycast_param* reflect_rcp = init_raycast_param(new_ray, rcp->w, rcp->reflection-1, 0, 1);
    ray_cast(reflect_rcp);
    free(reflect_rcp);

    float init_color[3];
    float reflect_color[3];
    float absorbed = 1.0-reflected;
    scale(ry->last_hit->color, absorbed, init_color);
    scale(new_ray->last_hit->color, reflected, reflect_color);
    add(init_color, reflect_color, ry->last_hit->color);
    free(new_ray);
}