#include <stdio.h>
#include <err.h>
#include "../utils/daft_math.h"
#include "./mesh_builder.h"

#pragma once

int load_object(char* path, world* w, float scale, float pos[3], material* mat);
