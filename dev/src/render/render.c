#include "../../include/render/render.h"

void get_background(raycast_param* rcp){
    if(rcp->w->skybox != NULL){
        float dir[3];
        scale(rcp->r->dir, -1, dir);
        float u = 0.5+ (atan2f(dir[0], dir[2])/(M_PI*2));
        float v = 0.5+ (asinf(dir[1])/M_PI);
        SDL_Surface* sb = rcp->w->skybox;
        int x = u*sb->w;
        int y = v*sb->h;
        Uint32 pixel = ((Uint32*)sb->pixels)[y*sb->w+x];
        Uint8 r, g, b;
        SDL_GetRGB(pixel, sb->format, &r,&g,&b);
        ray_update_result(rcp->r, NULL, INFINITY, (float[]){0,0,0}, NULL, (float[]){r/255.0, g/255.0, b/255.0});
    }else
        ray_update_result(rcp->r, NULL, INFINITY, (float[]){0,0,0}, NULL, (float[]){0,0,0});
}

//free the raycast_param
void ray_cast(raycast_param* rcp){
    ray* r = rcp->r;
    world* w = rcp->w;
    if(rcp->reflection < 0){
        get_background(rcp);
        return;
    }
    if(rcp->compute_masks)
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
    if(rcp->show_lights){
        for(int i = 0; i < w->size_lights; i++){
            light* l = w->lights[i];
            r->current_mesh = NULL;
            sphere_render(l->s, r);
        }
    }
    if (rcp->show_campoints)
    {
        for (int i = 0; i < w->size_campoints; i++)
        {
            campoint* cp = &w->campoints[i];
            r->current_mesh = NULL;
            sphere_render(cp->s, r);
        }
    }
    if(r->last_hit != NULL){
        reflection(rcp);
        shadow_render(rcp);
    }else if(rcp->skybox)
        get_background(rcp);
    free(rcp);
}


