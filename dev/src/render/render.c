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
        ray_update_result(ry, NULL, INFINITY, (float[]){r/255.0,g/255.0,b/255.0});
    }else
        ray_update_result(ry, NULL, INFINITY, (float[]){0,0,0});
}

void ray_cast(ray* r, world* w, camera* cam){
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
}