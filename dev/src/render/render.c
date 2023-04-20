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

void _ray_cast(ray* r, world* w, int reflection_count, int compute_shadow){
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
    if(r->last_hit != NULL){
        if(reflection_count && r->last_hit->reflectivity > 0)
            reflection(r, w, reflection_count);
        if(compute_shadow)
            shadow_render(r, w);
    }
}

void basic_ray_cast(ray* r, world* w){
    _ray_cast(r, w, 0, 0);
}

void ray_cast_reflection(ray* r, world* w, int nb_reflections){
    _ray_cast(r, w, nb_reflections, 0);
}

void ray_cast(ray* r, world* w, int reflection, int compute_shadow){
    if(reflection)
        _ray_cast(r, w, MAXREFLECTIONS, compute_shadow);
    else
        _ray_cast(r, w, 0, compute_shadow);
}


