#include "../../include/architecture/camera.h"

Vector3 createRay(Camera* cam, int x, int y){
    float yaw = cam->rotation.y;
    float pitch = cam->rotation.x;
    float height = SCREEN_HEIGHT;
    float width = SCREEN_WIDTH;
    #if SCREEN_WIDTH > 1 || SCREEN_HEIGHT > 1
    height -= 1;
    width -= 1;
    #endif 
    float ratioX = ((float)x / height) - 0.5;
    float ratioY = ((float)y / width) - 0.5;
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
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            camera->rays[y*SCREEN_WIDTH+x] = createRay(camera, x, y);
        }
    }
    return camera;
}