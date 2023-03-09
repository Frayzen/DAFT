#include "../../include/architecture/bbox.h"

bbox * init_bbox(float min[3], float max[3])
{
        bbox *b = malloc(sizeof(bbox));
        b->min[0] = min[0];
        b->min[1] = min[1];
        b->min[2] = min[2];
        b->max[0] = max[0];
        b->max[1] = max[1];
        b->max[2] = max[2];
        return b;
}

void free_bbox(bbox *b)
{
        free(b);
}