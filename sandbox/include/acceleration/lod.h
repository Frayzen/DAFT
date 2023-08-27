#ifndef LOD_H
#define LOD_H

#include "../architecture/mesh.h"
#include <string.h>
#include "../architecture/vectors.h"
#include <stdlib.h>

typedef struct Edge {
    int v1;
    int v2;
    Vector3 newPoint;
    float cost;
    struct Edge* next;
} Edge;

#define LOD_THRESHOLD 0

void simplifyMesh(Mesh* mesh);

#endif