#include "../../include/architecture/light.h"

light* init_light(float pos[3], float color[3], float intensity){
    light* lt = calloc(sizeof(light), 1);
    lt->pos[0] = pos[0];
    lt->pos[1] = pos[1];
    lt->pos[2] = pos[2];
    lt->color[0] = color[0];
    lt->color[1] = color[1];
    lt->color[2] = color[2];
    lt->intensity = intensity;
    return lt;
}
void free_light(light* lt){
    free(lt);
}