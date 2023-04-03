#include "../../include/render/render.h"

void get_background(ray* ry, camera* cam){
    if(cam->skybox != NULL){
        float dir[3];
        scale(ry->dir, -1, dir);
        float u = 0.5+ (atan2f(dir[0], dir[2])/(M_PI*2));
        float v = 0.5+ (asinf(dir[1])/M_PI);
        SDL_Surface* skybox = cam->skybox;
        int x = u*skybox->w;
        int y = v*skybox->h;
        Uint32 pixel = ((Uint32*)skybox->pixels)[y*skybox->w+x];
        Uint8 r, g, b;
        SDL_GetRGB(pixel, skybox->format, &r,&g,&b);
        ray_update_result(ry, NULL, INFINITY, (float[]){r/255.0,g/255.0,b/255.0}, (float[]){0,0,0}, 0);
    }else
        ray_update_result(ry, NULL, INFINITY, (float[]){0,0,0}, (float[]){0,0,0}, 0);
}


void _ray_cast(ray* r, world* w, camera* cam, int depth){
    if(depth > MAXREFLECTIONS)
        return;
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
        get_background(r, cam);
    else if(cam->quailty == 1)
        reflection(r, w, cam, depth);
}

void reflection(ray * ry, world * w, camera * cam, int depth)
{
    float d_n = dotProduct(ry->last_hit->normal, ry->dir);
    float new_dir[3];
    scale(ry->last_hit->normal, d_n*2, new_dir);
    minus(ry->dir, new_dir, new_dir);
    ray * new_ray = malloc(sizeof(ray));
    scale(ry->dir, ry->last_hit->mint, new_ray->pos);
    copy(new_ray->dir, new_dir);
    new_ray->last_hit = NULL;
    new_ray->mint = INFINITY;

    _ray_cast(new_ray, w, cam, depth +1);

    scale(ry->last_hit->color, ry->last_hit->reflectivity, ry->last_hit->color);
    if(new_ray->last_hit != NULL){
        scale(new_ray->last_hit->color, 1 - ry->last_hit->reflectivity, new_ray->last_hit->color);
        add(ry->last_hit->color, new_ray->last_hit->color, ry->last_hit->color);
    }
    free(new_ray);
}


void ray_cast(ray* r, world* w, camera* cam){
    _ray_cast(r, w, cam, 0);
}


