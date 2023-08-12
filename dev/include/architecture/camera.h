#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "../architecture/vectors.h"

#ifndef CAMERA_H
#define CAMERA_H
typedef struct camera
{
    //position of the camera
	float3 pos;
    //pitch and yaw of the camera
    float pitch;
    float yaw;
    //field of view in degree (90 - 120 degrees)
    int FOV_x;
    int FOV_y;
    float3 movement_speed;
    float2 rotation_speed;
    //if the camera is real time, quality is 0
    int quality;
}camera;

//init camera
camera* init_camera(float3 pos, float pitch, float yaw, int FOV_x, int FOV_y);
#endif