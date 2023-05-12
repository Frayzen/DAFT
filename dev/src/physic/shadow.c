#include "../../include/physic/shadow.h"

void shadow_render(raycast_param* rcp)
{
    ray* ry = rcp->r;
    world* w = rcp->w;
    ray* shadow_ray = calloc(sizeof(struct ray),1);

    //Define the position of the shadow ray
    scale(ry->dir, ry->last_hit->mint, shadow_ray->pos);
    float litl_norm[3];
    scale(ry->last_hit->normal, 0.0001, litl_norm);
    add(shadow_ray->pos, litl_norm, shadow_ray->pos);
    add(ry->pos, shadow_ray->pos, shadow_ray->pos);
    for (int i = 0; i < w->size_lights; i++){
        float dir_light[3];
        minus(ry->last_hit->point, w->lights[i]->pos, dir_light);
        normalize(dir_light, dir_light);
        float dpd = dotProduct(ry->last_hit->normal, dir_light);
        dpd = max(MIN_DIFUSE_LIGHT, dpd);
        scale(ry->last_hit->color, dpd, ry->last_hit->color); 
        // //Define the direction of the shadow ray
        // minus(w->lights[i]->pos, shadow_ray->pos, shadow_ray->dir);
        // float mint = norm(shadow_ray->dir);
        
        // //Normalize the direction vector
        // normalize(shadow_ray->dir,shadow_ray->dir);
        // float c = 1/mint * w->lights[i]->intensity;

        
        // shadow_ray->last_hit = calloc(sizeof(struct ray_result),1);
        // shadow_ray->last_hit->mint = mint;
        
        // raycast_param* shadow_rcp = init_raycast_param(shadow_ray, rcp->w, 0, 0, 0);
        // ray_cast(shadow_rcp);
        // //if we hit somthing, set the color in black
        // float ns = dotProduct(ry->last_hit->normal, shadow_ray->dir);
        // if (shadow_ray->last_hit->mint == mint && ns > 0){
        //         //light
        //         scale(ry->last_hit->color, (1-c), ry->last_hit->color);
        // }       
        // else //shadow
        // {
        //     scale(ry->last_hit->color, cos(ns), ry->last_hit->color);
        // }
        // if(shadow_ray->last_hit)
        //     free(shadow_ray->last_hit);
    }
    free(shadow_ray);
}