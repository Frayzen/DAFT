#include "../../include/architecture/camera.h"

Vector3 createRay(Camera* cam, int y, int x){
    Vector2 FOV = cam->FOV;
    float px = (2*(x+0.5)/SCREEN_WIDTH - 1)*tan(FOV.x/2)*SCREEN_ASPECT_RATIO;
    float py = (1 - 2*(y+0.5)/SCREEN_HEIGHT)*tan(FOV.y/2);
    return normalize((Vector3){px, py, -1});
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
            cam->rays[i*SCREEN_WIDTH+j] = createRay(cam, j, i);
        }
    }
    return cam;
}