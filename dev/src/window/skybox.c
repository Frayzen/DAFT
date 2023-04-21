#include "../../include/window/skybox.h"

void get_skybox_point(float* direction, float* x, float* y){
    float dir[3];
    normalize(direction, dir);
    scale(dir, -1, dir);
    *x = 0.5+ (atan2f(dir[0], dir[2])/(M_PI*2));
    *y = 0.5+ (asinf(dir[1])/M_PI);
}

void define_sky_scales(float from_scale[2], float to_scale[2], raycast_params* rcp){
    float from[3];
    float to[3];
    copy(rcp->botLeftCorner, from);
    copy(rcp->botLeftCorner, to);
    add(to, rcp->rightDir, to);
    add(to, rcp->topDir, to);
    get_skybox_point(from, &from_scale[0], &from_scale[1]);
    get_skybox_point(to, &to_scale[0], &to_scale[1]);
}

void set_rect(float from[2], float to[2], SDL_Rect* srcRect, SDL_Rect* toRect, raycast_params* rcp){
    float sh = rcp->height*rcp->screen_scale;
    float sw = rcp->width*rcp->screen_scale;
    srcRect->x = from[0]*rcp->w->skybox->w;
    srcRect->y = from[1]*rcp->w->skybox->h;
    srcRect->w = (to[0]-from[0])*rcp->w->skybox->w;
    srcRect->h = (to[1]-from[1])*rcp->w->skybox->h;
    toRect->x = from[0]*sw;
    toRect->y = from[1]*sh;
    toRect->w = (to[0]-from[0])*sw;
    toRect->h = (to[1]-from[1])*sh;
}

void define_sky_points(SDL_Rect* first_src, SDL_Rect* second_src, SDL_Rect* first_to, SDL_Rect* second_to, raycast_params* rcp){
    float from_scale[2], to_scale[2];
    float split_screen[2];
     
    define_sky_scales(from_scale, to_scale, rcp);
    if(from_scale[0] > to_scale[0]){
        set_rect((float[2]){0,0}, to_scale, first_src, first_to, rcp);
        set_rect(from_scale, (float[2]){1,1}, second_src, second_to, rcp);
    }else{
        set_rect(from_scale, to_scale, first_src, first_to, rcp);
        second_src->w = 0;
        second_to->w = 0;
    }
}
