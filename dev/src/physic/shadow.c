#include "../../include/physic/shadow.h"

void shadow_render(raycast_param* rcp)
{
    ray* ry = rcp->r;
    world* w = rcp->w;
    ray* shadow_ray = calloc(sizeof(struct ray),1);

    //Define the position of the shadow ray
    scale(ry->dir, (ry->last_hit->mint - 0.00001), shadow_ray->pos);
    add(ry->pos, shadow_ray->pos, shadow_ray->pos);
    //printf("triangle : %f\n", ry->last_hit->tri->normal);
    //Define the normal of the triangle hit by ry
    float normal[3] ={0,0,0};
    normalize(ry->last_hit->normal,normal);

    int size = w->size_lights;
    for (int i = 0; i < size; i++){
        //Define the direction of the shadow ray
        minus(w->lights[i]->pos, shadow_ray->pos, shadow_ray->dir);
        
        //Normalize the direction vector
        normalize(shadow_ray->dir,shadow_ray->dir);
        float mint = distance(shadow_ray->pos, w->lights[i]->pos)+0.01;
        float c = 1/mint * w->lights[i]->intensity;

        //float coeff[3] = {c,c,c};
        
        shadow_ray->last_hit = calloc(sizeof(struct ray_result),1);
        shadow_ray->last_hit->mint = mint;
        
        raycast_param* shadow_rcp = init_raycast_param(shadow_ray, rcp->w, 0, 0, 0);
        ray_cast(shadow_rcp);
        free(shadow_rcp);
        //if we hit somthing, set the color in black
        float x = dotProduct(normal, shadow_ray->dir);
        if (shadow_ray->last_hit->mint == mint && x > 0){


                //light
                ry->last_hit->color[0] = ((1 -ry->last_hit->color[0])*c+ry->last_hit->color[0]);
                ry->last_hit->color[1] = ((1 -ry->last_hit->color[1])*c+ry->last_hit->color[1]);
                ry->last_hit->color[2] = ((1 -ry->last_hit->color[2])*c+ry->last_hit->color[2]);
        }       
        else //shadow
        {
            float sqtc = sqrt(c);
            scale(ry->last_hit->color, sqtc, ry->last_hit->color);
        }
        if(shadow_ray->last_hit)
            free(shadow_ray->last_hit);
    }
    free(shadow_ray);
}