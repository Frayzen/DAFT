#include "../../include/physic/reflection.h"

void reflection(raycast_param* rcp){
    if(!rcp->reflection)
        return;
    if(rcp->r->last_hit->mat->reflection == 0)
        return;
            
    ray* ry = rcp->r;

    float d_n = dotProduct(ry->last_hit->normal, ry->dir);
    float new_dir[3];
    scale(ry->last_hit->normal, d_n*2, new_dir);
    minus(ry->dir, new_dir, new_dir);
    
    ray* new_ray = malloc(sizeof(ray));
    
    scale(ry->dir, ry->last_hit->mint, new_ray->pos);
    float litl_norm[3];
    scale(ry->last_hit->normal, 0.0001, litl_norm);
    add(new_ray->pos, litl_norm, new_ray->pos);
    add(ry->pos, new_ray->pos, new_ray->pos);

    normalize(new_dir, new_ray->dir);

    float reflected = ry->last_hit->mat->reflection;
    new_ray->last_hit = NULL;
    
    raycast_param* reflect_rcp = init_raycast_param(new_ray, rcp->w, rcp->reflection-1, 0, 0, 1);
    ray_cast(reflect_rcp);

    float init_color[3];
    float reflect_color[3];
    float absorbed = 1.0-reflected;
    scale(ry->last_hit->color, absorbed, init_color);
    scale(new_ray->last_hit->color, reflected, reflect_color);
    add(init_color, reflect_color, ry->last_hit->color);
    if(new_ray->last_hit)
        free(new_ray->last_hit);
    free(new_ray);
}