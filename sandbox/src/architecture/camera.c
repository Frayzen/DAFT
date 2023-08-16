#include "../../include/architecture/camera.h"

Vector3 createRay(Camera* cam, int y, int x){
    float yaw = cam->rotation.y;
    float pitch = cam->rotation.x;
    float ratioX = ((float)x / (float)SCREEN_WIDTH) - 1;
    float ratioY = ((float)y / (float)SCREEN_HEIGHT) - 1;
    yaw += ratioX * cam->FOV.x;
    pitch += ratioY * cam->FOV.y;
    Vector3 ray = {cos(pitch) * cos(yaw), sin(pitch), cos(pitch) * sin(yaw)};
    return ray;
}

Camera* createCamera(){
    Camera* camera = calloc(sizeof(Camera), 1);
    camera->FOV.x = CAM_FOV;
    camera->FOV.y = CAM_FOV;
    camera->rays = calloc(sizeof(Vector3), SCREEN_HEIGHT*SCREEN_WIDTH);
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            camera->rays[i*SCREEN_WIDTH+j] = createRay(camera, j+1, i+1);
            printf("ray %d %d : %f %f %f\n", i, j, camera->rays[i*SCREEN_WIDTH+j].x, camera->rays[i*SCREEN_WIDTH+j].y, camera->rays[i*SCREEN_WIDTH+j].z);
        }
    }
    return camera;
}