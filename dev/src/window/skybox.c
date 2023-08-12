#include "../../include/window/skybox.h"

void load_skybox(world* wd, char* path){
SDL_Surface* surface = IMG_Load(path);
    if(surface == NULL){
        printf("The skybox '%s' could not be loaded\n", path);
        return;
    }
    wd->skybox = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_FreeSurface(surface);
    printf("Skybox '%s' loaded !\n", path);
}

float2 get_skybox_point(float3 direction){
    float3 dir = normalize(direction);
    scale(dir, -1, dir);
    float2 r = { 0.5- (atan2f(dir.x, dir.z)/(M_PI*2)), 0.5+ (asinf(dir.y)/M_PI)};
    return r;
}

void define_sky_scales(float2* from_scale, float2* to_scale, rendering_params* rdp){
    float3 from;
    float3 to;
    copy(rdp->botLeftCorner, from);
    copy(rdp->botLeftCorner, to);
    add(to, rdp->rightDir, to);
    add(to, rdp->topDir, to);
    *from_scale =  get_skybox_point(from);
    *to_scale = get_skybox_point(to);
}

void render_on_screen(SDL_Renderer* renderer, SDL_Texture* texture, rendering_params* rdp, float fromSbX, float fromSbY, float toSbX, float toSbY, float fromScX, float fromScY, float toScX, float toScY){
    SDL_Rect src;
    SDL_Rect dest;
    
    src.x = fromSbX*rdp->w->skybox->w;
    dest.x = fromScX*rdp->screen_width;
    
    src.y = fromSbY*rdp->w->skybox->h;
    dest.y = fromScY*rdp->screen_height;

    src.w = rdp->w->skybox->w * (toSbX - fromSbX);
    dest.w = rdp->screen_width * (toScX - fromScX);

    src.h = rdp->w->skybox->h * (toSbY - fromSbY);
    dest.h = rdp->screen_height * (toScY - fromScY);

    SDL_RenderCopy(renderer, texture, &src, &dest);
}

void define_sky_points(SDL_Renderer* renderer, SDL_Texture* skybox_texture, rendering_params* rdp){
    float from_scale[2], to_scale[2];
    define_sky_scales(from_scale, to_scale, rdp);
    if(from_scale[0] < to_scale[0]){
        render_on_screen(renderer, skybox_texture, rdp, from_scale[0], from_scale[1], to_scale[0], to_scale[1], 0, 0, 1, 1);
    }
    else{
        float middleScreen = (1 - from_scale[0])/(1 - from_scale[0] + to_scale[0]);
        render_on_screen(renderer, skybox_texture, rdp, from_scale[0], from_scale[1], 1, to_scale[1], 0, 0, middleScreen, 1);
        render_on_screen(renderer, skybox_texture, rdp, 0, from_scale[1], to_scale[0], to_scale[1], middleScreen, 0, 1, 1);
    }
}
