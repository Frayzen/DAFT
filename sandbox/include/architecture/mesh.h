#ifndef HMESH
#define HMESH

#include "vectors.h"
#include "triangle.h"

typedef struct {
    unsigned int vertexCount;
    unsigned int normalCount;
    unsigned int uvCount;
    
    Vector3 *vertices;
    Vector3 *normals;
    Vector2 *uvs;

    unsigned int triangleCount;
    unsigned Triangle *triangles;
} Mesh;

Mesh* createMesh(const char* path);

#endif