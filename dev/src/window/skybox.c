#include "../../include/window/skybox.h"

void get_skybox_point(float* direction, float* x, float* y){
    float dir[3];
    normalize(direction, dir);
    scale(dir, -1, dir);
    *x = 0.5- (atan2f(dir[0], dir[2])/(M_PI*2));
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

void render_on_screen(SDL_Renderer* renderer, SDL_Texture* texture, raycast_params* rcp, float fromSbX, float fromSbY, float toSbX, float toSbY, float fromScX, float fromScY, float toScX, float toScY){
    SDL_Rect src;
    SDL_Rect dest;
    
    src.x = fromSbX*rcp->w->skybox->w;
    dest.x = fromScX*rcp->width * rcp->screen_scale;
    
    src.y = fromSbY*rcp->w->skybox->h;
    dest.y = fromScY*rcp->height * rcp->screen_scale;

    src.w = rcp->w->skybox->w * (toSbX - fromSbX);
    dest.w = rcp->width * rcp->screen_scale * (toScX - fromScX);

    src.h = rcp->w->skybox->h * (toSbY - fromSbY);
    dest.h = rcp->height * rcp->screen_scale * (toScY - fromScY);

    SDL_RenderCopy(renderer, texture, &src, &dest);
}

void define_sky_points(SDL_Renderer* renderer, SDL_Texture* skybox_texture, raycast_params* rcp){
    float from_scale[2], to_scale[2];
    define_sky_scales(from_scale, to_scale, rcp);
    if(from_scale[0] < to_scale[0]){
        render_on_screen(renderer, skybox_texture, rcp, from_scale[0], from_scale[1], to_scale[0], to_scale[1], 0, 0, 1, 1);
    }
    else{
        float middleScreen = (1 - from_scale[0])/(1 - from_scale[0] + to_scale[0]);
        render_on_screen(renderer, skybox_texture, rcp, from_scale[0], from_scale[1], 1, to_scale[1], 0, 0, middleScreen, 1);
        render_on_screen(renderer, skybox_texture, rcp, 0, from_scale[1], to_scale[0], to_scale[1], middleScreen, 0, 1, 1);
    }
}
