#include "../../include/render/shadow.h"

//check if the shadow_ray touches the light
//returns 1 if hit an object, 0 otherwise ()
int shadow_hit(ray* shadow_ray, light* l, float prevt)
    {/*
    float exp_dir[3];
    scale(shadow_ray->dir,shadow_ray->last_hit->mint, exp_dir)
    add(shadow_ray->pos,l->pos, exp_dir);
    */
    if (shadow_ray->last_hit->tri != NULL)
        return 1;
    if (shadow_ray->last_hit->mint != prevt)
        return 1;

    return 0;
    
        
}

void shadow_render(ray* ray, world* w, int real_time)
{
    struct ray* sRay = calloc(sizeof(struct ray),0);
    //Define the position of the shadow ray
    scale(ray->dir, ray->last_hit->mint, sRay->pos);
    add(ray->pos, sRay->pos, sRay->pos);

    int size = w->size_lights;
    for (int i = 0; i < size; i++){

        //Define the direction of the shadow ray
        minus(sRay->pos, w->lights[i]->pos, sRay->dir);
        //Normalize the direction vector
        normalize(sRay->dir,sRay->dir);
        
        sRay->current_mesh = ray->current_mesh;
        sRay->last_hit = calloc(sizeof(struct ray_result),0);
        sRay->last_hit->mint = distance(sRay->pos, w->lights[i]->pos);
        float prevt = sRay->last_hit->mint;
        ray_cast(sRay, w, NULL);

        //if we hit somthing, set the color in black
        if (shadow_hit(sRay, w->lights[i],prevt) == 1){
            ray->last_hit->color[0] = 0;
            ray->last_hit->color[1] = 0;
            ray->last_hit->color[2] = 0;
        }
        free(sRay->last_hit);
    }
    free(sRay);
}