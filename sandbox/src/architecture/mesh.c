#include "../../include/architecture/mesh.h"

Mesh* createMesh(char* path, Transform transform) {
    Mesh* mesh = malloc(sizeof(Mesh));
    parseObjFile(path, mesh, &transform);
    printf("Mesh %s created (%d vertices, %d faces)\n", path, mesh->vertexCount, mesh->triangleCount);
    return mesh;
}

void clearMesh(Mesh* m) {
    m->vertexCount = 0;
    m->normalCount = 0;
    m->uvCount = 0;
    m->triangleCount = 0;
}

void freeMesh(Mesh* m) {
    if(m->vertices != NULL) free(m->vertices);
    if(m->normals != NULL) free(m->normals);
    if(m->uvs != NULL) free(m->uvs);
    if(m->triangles != NULL) free(m->triangles);
    free(m);
}

