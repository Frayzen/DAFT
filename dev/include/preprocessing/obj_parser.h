#include <stdio.h>
#include <err.h>
#include "../utils/daft_math.h"
#include "../../include/preprocessing/mtl_parser.h"
#include "./mesh_builder.h"

#pragma once

void load_object(char* path, world* w, float scale, float pos[3], char* texture_path);
