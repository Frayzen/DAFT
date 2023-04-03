#include "../utils/daft_math.h"
#include "./mesh_builder.h"

#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

void load_object(world* w, char* file, float scale, float pos[3], float reflectivity);
#endif