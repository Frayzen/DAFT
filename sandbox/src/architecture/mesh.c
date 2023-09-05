#include "../../include/architecture/mesh.h"

Mesh* createMesh(char* path, Transform transform) {
    Mesh* mesh = malloc(sizeof(Mesh));
    parseObjFile(path, mesh, &transform);
    buildBbox(mesh);
    printf("Mesh %s created (%d vertices, %d faces, %d bboxes)\n", path, mesh->vertexCount, mesh->triangleCount, mesh->bboxCount);
    printf("Simplifying mesh...\n");
    //simplifyMesh(mesh);
    printf("Mesh simplified (%d vertices, %d faces, %d bboxes)\n", mesh->vertexCount, mesh->triangleCount, mesh->bboxCount);
    return mesh;
}

void clearMesh(Mesh* m) {
    m->vertexCount = 0;
    m->normalCount = 0;
    m->uvCount = 0;
    m->triangleCount = 0;
    m->bboxCount = 0;
}

void freeMesh(Mesh* m) {
    if(m->vertices != NULL) free(m->vertices);
    if(m->normals != NULL) free(m->normals);
    if(m->uvs != NULL) free(m->uvs);
    if(m->triangles != NULL) free(m->triangles);
    if(m->maxBbox != NULL) free(m->maxBbox);
    if(m->minBbox != NULL) free(m->minBbox);
    if(m->children != NULL) free(m->children);
    if(m->originChildren != NULL) free(m->originChildren);
    free(m);
}

