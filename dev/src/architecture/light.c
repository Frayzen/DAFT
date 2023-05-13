#include "../../include/architecture/light.h"

//intensity > 1
light* init_light(float pos[3], illumination illum){
    light* lt = calloc(sizeof(light), 1);
    copy(pos, lt->pos);
    lt->illum = illum;
    return lt;
}