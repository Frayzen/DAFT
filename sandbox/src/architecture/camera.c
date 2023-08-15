#include "../../include/architecture/camera.h"

Camera* createCamera(Vector3 pos, Vector2 angles, Vector2 FOV){
    Camera* cam = calloc(sizeof(Camera), 1);
    cam->pos = pos;
    cam->angles = angles;
    cam->FOV = FOV;
    return cam;
}