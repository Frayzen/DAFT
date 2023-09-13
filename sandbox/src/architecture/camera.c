#include "../../include/architecture/camera.h"

Vector3 createRay(Camera* cam, int x, int y){
    float yaw = cam->rotation.y;
    float pitch = cam->rotation.x;
    float ratioX = ((float)x / SCREEN_WIDTH) - 0.5;
    float ratioY = 0.5 - ((float)y / SCREEN_HEIGHT);
    yaw += ratioX * cam->FOV.x * SCREEN_ASPECT_RATIO;
    pitch += ratioY * cam->FOV.y;
    Vector3 ray = {cos(pitch) * cos(yaw), sin(pitch), cos(pitch) * sin(yaw)};
    return ray;
}

Matrix4 getProjectionMatrix(Camera* cam){
    Matrix4 projectionMatrix = {0};
    float fovX = cam->FOV.x;
    float fovY = cam->FOV.y;
    float aspectRatio = SCREEN_ASPECT_RATIO;
    float near = 0.1;
    float far = 100;
    float fovXScale = 1 / tan(fovX / 2);
    float fovYScale = 1 / tan(fovY / 2);
    projectionMatrix.r1[1] = fovXScale / aspectRatio;
    projectionMatrix.r2[2] = fovYScale;
    projectionMatrix.r3[3] = (far + near) / (near - far);
    projectionMatrix.r3[4] = (2 * far * near) / (near - far);
    projectionMatrix.r4[3] = -1;
    return projectionMatrix;
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