#ifndef MESH_H
#define MESH_H
#include "vectors.h"
#include "triangle.h"
typedef struct {
    int vertexCount;
    int normalCount;
    int uvCount;
    int triangleCount;
    
    Vector3 *vertices;
    Vector3 *normals;
    Vector2 *uvs;
    Triangle *triangles;

} Mesh;
#include <stdlib.h>
#include "../preprocessing/obj_parser.h"

Mesh* createMesh(char* path);
void clearMesh(Mesh* m);
void freeMesh(Mesh* m);

#endif