#include <SDL2/SDL.h>
#include <stdlib.h>

#pragma once
typedef struct camera
{
    //position of the camera
	float pos[3];
    //pitch and yaw of the camera
    float pitch;
    float yaw;
    //field of view in degree (90 - 120 degrees)
    int FOV;
    //skybox texture, NULL if no skybox
    SDL_Surface* skybox;

}camera;

//init camera
camera* init_camera(float pos[3], float pitch, float yaw, int FOV, SDL_Surface* skybox);
//free camera
void free_camera(camera* cam);