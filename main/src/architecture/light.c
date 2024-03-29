#include "../../include/architecture/light.h"

//intensity > 1
light* init_light(float pos[3], float color[3]){
    light* lt = calloc(sizeof(light), 1);
    copy(pos, lt->pos);
    copy(color, lt->color);
    sphere* s = sphere_init(pos[0], pos[1], pos[2], 0.1, create_mat_from_color(color[0], color[1], color[2]));
    lt->s = s;
    return lt;
}

void free_light(light* lt){
    free(lt->s);
    free(lt);
}