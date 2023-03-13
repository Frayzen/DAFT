#include "../../include/architecture/camera.h"

camera* init_camera(float pos[3], float pitch, float yaw, int FOV, SDL_Surface* skybox){
    camera* cam = calloc(sizeof(camera), 1);
    cam->pos[0] = pos[0];
    cam->pos[1] = pos[1];
    cam->pos[2] = pos[2];
    cam->pitch = pitch;
    cam->yaw = yaw;
    cam->FOV = FOV;
    cam->skybox = skybox;
    return cam;
}

void free_camera(camera* cam){
    if(cam->skybox != NULL){
        SDL_FreeSurface(cam->skybox);
    }
    free(cam);
}