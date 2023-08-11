#include <stdio.h>
#include "../utils/daft_math.h"
#include "../../include/preprocessing/mtl_parser.h"
#include "./mesh_builder.h"
#include <string.h>

#pragma once

int load_object(char* path, world* w, float scale, float pos[3], float rot[3], char* rel_path);
