#include "../../include/architecture/campoint.h"

campoint *init_campoint(float3 pos, float yaw, float pitch)
{
    campoint *cp = malloc(sizeof(campoint));
    cp->yaw = yaw;
    cp->pitch = pitch;
    cp->time = 1;
    sphere* s = sphere_init(pos, 0.1, create_mat_from_color(225, 0, 0));
    cp->s = s;
    return cp;
}