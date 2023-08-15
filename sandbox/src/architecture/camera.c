#include "../../include/architecture/camera.h"

Camera* createCamera(){
    Camera* cam = calloc(sizeof(Camera), 1);
    cam->FOV.x = CAM_FOV;
    cam->FOV.y = CAM_FOV;
    return cam;
}