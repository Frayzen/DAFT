#ifndef BVH_H
#define BVH_H

#include "mesh.h"
#include "vectors.h"

void buildBbox(Mesh* mesh);
void rebuildBbox(Mesh* mesh);

#endif