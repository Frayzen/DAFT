#include "../../include/physic/shadow.h"

void shadow_render(ray* ry, world* w)
{
    struct ray* sRay = calloc(sizeof(struct ray),1);

    //Define the position of the shadow ray
    scale(ry->dir, (ry->last_hit->mint - 0.00001), sRay->pos);
    add(ry->pos, sRay->pos, sRay->pos);
    //printf("triangle : %f\n", ry->last_hit->tri->normal);
    //Define the normal of the triangle hit by ry
    float normal[3] ={0,0,0};
    normalize(ry->last_hit->normal,normal);

    int size = w->size_lights;
    for (int i = 0; i < size; i++){
        //Define the direction of the shadow ray
        minus(w->lights[i]->pos, sRay->pos, sRay->dir);
        
        //Normalize the direction vector
        normalize(sRay->dir,sRay->dir);
        float mint = distance(sRay->pos, w->lights[i]->pos)+0.01;
        float c = 1/mint * w->lights[i]->intensity;

        //float coeff[3] = {c,c,c};
        
        sRay->last_hit = calloc(sizeof(struct ray_result),1);
        sRay->last_hit->mint = mint;
        basic_ray_cast(sRay, w);
        
        //if we hit somthing, set the color in black
        float x = dotProduct(normal, sRay->dir);
        if (sRay->last_hit->mint == mint && x > 0){


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
        if(sRay->last_hit)
            free(sRay->last_hit);
    }
    free(sRay);
}