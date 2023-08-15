#include "../../include/window/skybox.h"

void load_skybox(World* wd, char* path){
    SDL_Surface* surface = IMG_Load(path);
    if(surface == NULL){
        printf("The skybox '%s' could not be loaded\n", path);
        return;
    }
    wd->skybox = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_FreeSurface(surface);
    printf("Skybox '%s' loaded !\n", path);
}

Vector2 get_skybox_point(Vector3 direction){
    Vector3 dir = normalize(direction);
    dir = scale(dir, -1);
    Vector2 r = { 0.5- (atan2f(dir.x, dir.z)/(M_PI*2)), 0.5+ (asinf(dir.y)/M_PI)};
    return r;
}

Vector3 get_ray_direction(int width, int height, int x_pix, int y_pix, Camera *cam)
{
    float yaw = cam->angles.x;
    float pitch = cam->angles.y;
    float FOV_x = cam->FOV.x * M_PI / 180;
    float FOV_y = cam->FOV.y * M_PI / 180;
    float ratioX = ((float)x_pix / (float)width) - 0.5;
    float ratioY = ((float)y_pix / (float)height) - 0.5;
    yaw += ratioX * FOV_x;
    pitch += ratioY * FOV_y;
    Vector3 dir = {cos(pitch) * cos(yaw), sin(pitch), cos(pitch) * sin(yaw)};
    return dir;
}

void define_sky_scales(Vector2* from_scale, Vector2* to_scale, World* wd){
    Vector3 from = get_ray_direction(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, wd->cam);
    Vector3 to = get_ray_direction(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, wd->cam);
    *from_scale =  get_skybox_point(from);
    *to_scale = get_skybox_point(to);
}

void render_on_screen(SDL_Renderer* renderer, SDL_Texture* texture, World* wd, float fromSbX, float fromSbY, float toSbX, float toSbY, float fromScX, float fromScY, float toScX, float toScY){
    SDL_Rect src;
    SDL_Rect dest;
    
    src.x = fromSbX*wd->skybox->w;
    dest.x = fromScX*SCREEN_WIDTH;
    
    src.y = fromSbY*wd->skybox->h;
    dest.y = fromScY*SCREEN_HEIGHT;

    src.w = wd->skybox->w * (toSbX - fromSbX);
    dest.w = SCREEN_WIDTH * (toScX - fromScX);

    src.h = wd->skybox->h * (toSbY - fromSbY);
    dest.h = SCREEN_HEIGHT * (toScY - fromScY);

    SDL_RenderCopy(renderer, texture, &src, &dest);
}

void define_sky_points(SDL_Renderer* renderer, SDL_Texture* skybox_texture, World* wd){
    Vector2 from_scale, to_scale;
    define_sky_scales(&from_scale, &to_scale, wd);
    if(from_scale.x < to_scale.x){
        render_on_screen(renderer, skybox_texture, wd, from_scale.x, from_scale.y, to_scale.x, to_scale.y, 0, 0, 1, 1);
    }
    else{
        float middleScreen = (1 - from_scale.x)/(1 - from_scale.x + to_scale.x);
        render_on_screen(renderer, skybox_texture, wd, from_scale.x, from_scale.y, 1, to_scale.y, 0, 0, middleScreen, 1);
        render_on_screen(renderer, skybox_texture, wd, 0, from_scale.y, to_scale.x, to_scale.y, middleScreen, 0, 1, 1);
    }
}
