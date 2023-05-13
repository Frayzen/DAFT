#include "../../include/architecture/light.h"

//intensity > 1
light* init_light(float pos[3], float color[3]){
    light* lt = calloc(sizeof(light), 1);
    copy(pos, lt->pos);
    copy(color, lt->color);
    return lt;
}