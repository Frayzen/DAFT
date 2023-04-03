#include "../../include/render/render.h"

void get_background(ray* ry, world* wd){
    if(wd->skybox != NULL){
        float dir[3];
        scale(ry->dir, -1, dir);
        float u = 0.5+ (atan2f(dir[0], dir[2])/(M_PI*2));
        float v = 0.5+ (asinf(dir[1])/M_PI);
        int x = u*wd->skybox->w;
        int y = v*wd->skybox->h;
        Uint32 pixel = ((Uint32*)wd->skybox->pixels)[y*wd->skybox->w+x];
        Uint8 r, g, b;
        SDL_GetRGB(pixel, wd->skybox->format, &r,&g,&b);
        ray_update_result(ry, NULL, INFINITY, (float[]){r/255.0,g/255.0,b/255.0}, (float[]){0,0,0}, 0);
    }else
        ray_update_result(ry, NULL, INFINITY, (float[]){0,0,0}, (float[]){0,0,0}, 0);
}

void _ray_cast(ray* r, world* w, int real_time, int depth){
    if(depth >= MAXREFLECTIONS){
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
    else if(!real_time && r->last_hit->reflectivity > 0)
        reflection(r, w, depth);
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
    //normalize(ry->dir, new_ray->dir);
    new_ray->last_hit = NULL;
    
    _ray_cast(new_ray, w, 0, depth +1);

    float init_color[3];
    float reflect_color[3];
    float reflected = ry->last_hit->reflectivity;
    float absorbed = 1.0-reflected;
    scale(ry->last_hit->color, absorbed, init_color);
    scale(new_ray->last_hit->color, reflected, reflect_color);
    add(init_color, reflect_color, ry->last_hit->color);
    free(new_ray->last_hit);
    free(new_ray);
}


void ray_cast(ray* r, world* w, int real_time){
    _ray_cast(r, w, real_time, 0);
}


