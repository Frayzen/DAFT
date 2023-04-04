#include <stdio.h>
#include <err.h>
#include "../utils/daft_math.h"
#include "./mesh_builder.h"

#pragma once

void load_object(char* path, world* w, float scale, float p[3], float reflectivity);