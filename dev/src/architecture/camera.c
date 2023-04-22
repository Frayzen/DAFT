#include "../../include/architecture/camera.h"

camera* init_camera(float pos[3], float pitch, float yaw, int FOV_x, int FOV_y){
    camera* cam = calloc(sizeof(camera), 1);
    cam->pos[0] = pos[0];
    cam->pos[1] = pos[1];
    cam->pos[2] = pos[2];
    cam->pitch = pitch;
    cam->yaw = yaw;
    cam->FOV_x = FOV_x;
    cam->FOV_y = FOV_y;
    cam->movement_speed[0] = 0;
    cam->movement_speed[1] = 0;
    cam->rotation_speed[0] = 0;
    cam->rotation_speed[1] = 0;
    cam->quality = 0;
    return cam;
}