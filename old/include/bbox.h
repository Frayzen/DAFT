#include <string.h>
#include "architecture.h"
#pragma once
bbox* init_bbox();
size_t compute_depth(size_t nb_tri);
size_t compute_tri_last_level(size_t depth, size_t no_tri);
size_t compute_no_extra(size_t no_tri, size_t tri_last_level, size_t depth);
///nbcnr is number of children of next recursion
bbox* build_bbox(size_t depth, size_t no_tri, size_t no_extra);
void compute_bounds_tri(mesh* m, bbox* b);
void compute_bounds_bbox(bbox* b);
void add_tri_to_bbox(mesh* m, bbox *b, size_t depth, triangle *t);
void free_bbox(bbox* b);
