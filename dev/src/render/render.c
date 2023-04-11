#include "../../include/render/render.h"

void get_background(ray* ry, world* wd){
    if(wd->skybox != NULL){
        float dir[3];
        scale(ry->dir, -1, dir);
        float u = 0.5+ (atan2f(dir[0], dir[2])/(M_PI*2));
        float v = 0.5+ (asinf(dir[1])/M_PI);
        SDL_Surface* skybox = wd->skybox;
        int x = u*wd->skybox->w;
        int y = v*wd->skybox->h;
        Uint32 pixel = ((Uint32*)wd->skybox->pixels)[y*wd->skybox->w+x];
        Uint8 r, g, b;
        SDL_GetRGB(pixel, skybox->format, &r,&g,&b);
        ray_update_result(ry, NULL, INFINITY, (float[]){r/255.0,g/255.0,b/255.0}, (float[]){0,0,0}, 0);
    }else
        ray_update_result(ry, NULL, INFINITY, (float[]){0,0,0}, (float[]){0,0,0}, 0);
}

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
        ray_cast(sRay, w, 0, 0);
        
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
void _ray_cast(ray* r, world* w, int reflection_count, int allow_shadow){
    if(reflection_count < 0){
        get_background(r, w);
        return;
    }
    for(int idm = 0; idm < w->size_meshes; idm++){
        mesh* m = w->meshes[idm];
        r->current_mesh = m;
        mesh_render(m, r);
    }
    for(int ids = 0; ids < w->size_spheres; ids++){
        sphere* s = &w->spheres[ids];
        r->current_mesh = NULL;
        sphere_render(s, r);
    }
    if(r->last_hit == NULL)
        get_background(r, w);
    else{
        if(reflection_count && r->last_hit->reflectivity > 0)
            reflection(r, w, reflection_count);
        if(allow_shadow)
            shadow_render(r, w);
    }
}

void reflection(ray * ry, world * w, int depth)
{
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
    
    _ray_cast(new_ray, w, depth-1, 0);

    float init_color[3];
    float reflect_color[3];
    float absorbed = 1.0-reflected;
    scale(ry->last_hit->color, absorbed, init_color);
    scale(new_ray->last_hit->color, reflected, reflect_color);
    add(init_color, reflect_color, ry->last_hit->color);
    free(new_ray->last_hit);
    free(new_ray);
}


void ray_cast(ray* r, world* w, int reflection, int shadow){
    if(reflection)
        _ray_cast(r, w, MAXREFLECTIONS, shadow);
    else
        _ray_cast(r, w, 0, shadow);
}


