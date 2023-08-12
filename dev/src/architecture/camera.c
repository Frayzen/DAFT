#include "../../include/architecture/camera.h"

camera* init_camera(float3 pos, float pitch, float yaw, int FOV_x, int FOV_y){
    camera* cam = calloc(sizeof(camera), 1);
    cam->pos.x = pos.x;
    cam->pos.y = pos.y;
    cam->pos.z = pos.z;
    cam->pitch = pitch;
    cam->yaw = yaw;
    cam->FOV_x = FOV_x;
    cam->FOV_y = FOV_y;
    cam->movement_speed.x = 0;
    cam->movement_speed.y = 0;
    cam->movement_speed.z = 0;
    cam->rotation_speed.x = 0;
    cam->rotation_speed.y = 0;
    cam->quality = 0;
    return cam;
}