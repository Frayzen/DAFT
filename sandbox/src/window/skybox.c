#include "../../include/window/skybox.h"

void worldSetSkybox(World* wd, char* path){
    if(wd->skybox != NULL){
        SDL_FreeSurface(wd->skybox);
    }
    SDL_Surface* surface = IMG_Load(path);
    if(surface == NULL){
        printf("The skybox '%s' could not be loaded\n", path);
        return;
    }
    wd->skybox = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_FreeSurface(surface);
    printf("Skybox '%s' loaded !\n", path);
}

Vector2 getSkyboxPoint(Vector3 direction){
    Vector3 dir = normalize(direction);
    dir = scale(dir, -1);
    Vector2 r = { 0.5- (atan2f(dir.x, dir.z)/(M_PI*2)), 0.5+ (asinf(dir.y)/M_PI)};
    return r;
}

Vector3 getRayDirection(int width, int height, int xpix, int ypix, Camera *cam)
{
    float x = (2 * ((float)xpix + 0.5) / (float)width - 1) * tan(cam->FOV.x / 2 * M_PI / 180) * width / (float)height;
    float y = -(2 * ((float)ypix + 0.5) / (float)height - 1) * tan(cam->FOV.y / 2 * M_PI / 180);
    Vector3 dir = {x, y, -1};
    dir = normalize(dir);
    return dir;
}

void defineSkyScales(Vector2* from_scale, Vector2* to_scale, Camera* cam){
    Vector3 from = getRayDirection(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, cam);
    Vector3 to = getRayDirection(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, cam);
    *from_scale =  getSkyboxPoint(from);
    *to_scale = getSkyboxPoint(to);
}

void renderOnScreen(SDL_Renderer* renderer, SDL_Texture* texture, World* wd, float fromSbX, float fromSbY, float toSbX, float toSbY, float fromScX, float fromScY, float toScX, float toScY){
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

void defineSkyPoints(DaftApp* app, SDL_Texture* skybox_texture){
    Vector2 from_scale, to_scale;
    defineSkyScales(&from_scale, &to_scale, app->camera);
    if(from_scale.x < to_scale.x){
        renderOnScreen(app->renderer, skybox_texture, app->world, from_scale.x, from_scale.y, to_scale.x, to_scale.y, 0, 0, 1, 1);
    }
    else{
        float middleScreen = (1 - from_scale.x)/(1 - from_scale.x + to_scale.x);
        renderOnScreen(app->renderer, skybox_texture, app->world, from_scale.x, from_scale.y, 1, to_scale.y, 0, 0, middleScreen, 1);
        renderOnScreen(app->renderer, skybox_texture, app->world, 0, from_scale.y, to_scale.x, to_scale.y, middleScreen, 0, 1, 1);
    }
}
