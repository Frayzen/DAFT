#include <stdio.h>
#include <string.h>
#include "../architecture/vectors.h"
#include "../architecture/material.h"
#include "../utils/daft_math.h"
#include <assert.h>

void mtl_parser(const char* filename, const char* path, material** materials, int* numMaterials);
