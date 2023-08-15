#include "../../include/architecture/camera.h"

Vector3 createRay(int i, int j){
    Vector3 ray;
    ray.x = (2 * ((j + 0.5) / SCREEN_WIDTH) - 1) * tan(CAM_FOV / 2) * ASPECT_RATIO;
    ray.y = (1 - 2 * ((i + 0.5) / SCREEN_HEIGHT)) * tan(CAM_FOV / 2);
    ray.z = -1;
    return ray;
}

Camera* createCamera(){
    Camera* cam = calloc(sizeof(Camera), 1);
    cam->FOV.x = CAM_FOV;
    cam->FOV.y = CAM_FOV;
    cam->rays = calloc(sizeof(Vector3), SCREEN_HEIGHT*SCREEN_WIDTH);
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            cam->rays[i*SCREEN_WIDTH+j] = createRay(i, j);
        }
    }
    return cam;
}