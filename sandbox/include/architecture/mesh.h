#ifndef MESH_H
#define MESH_H
#include "vectors.h"
#include "triangle.h"
typedef struct {
    int vertexCount;
    int normalCount;
    int uvCount;
    int triangleCount;
    int bboxCount;
    
    Vector3 *vertices;
    Vector3 *normals;
    Vector2 *uvs;
    Triangle *triangles;

    Vector3 *minBbox;
    Vector3 *maxBbox;
    int2 *children;

} Mesh;
#include <stdlib.h>
#include "../preprocessing/obj_parser.h"
#include "transform.h"

Mesh* createMesh(char* path, Transform transform);
void clearMesh(Mesh* m);
void freeMesh(Mesh* m);

#endif