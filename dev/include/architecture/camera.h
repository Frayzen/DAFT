#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#ifndef CAMERA_H
#define CAMERA_H
typedef struct camera
{
    //position of the camera
	float pos[3];
    //pitch and yaw of the camera
    float pitch;
    float yaw;
    //field of view in degree (90 - 120 degrees)
    int FOV_x;
    int FOV_y;
    //skybox texture, NULL if no skybox
    SDL_Surface* skybox;
    float movement_speed[3];
    float rotation_speed[2];
    int quailty;
}camera;

//init camera
camera* init_camera(float pos[3], float pitch, float yaw, int FOV_x, int FOV_y, SDL_Surface* skybox);
//free camera
void free_camera(camera* cam);
void load_skybox(camera* cam, char* path);
#endif