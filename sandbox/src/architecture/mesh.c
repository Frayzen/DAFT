#include "../../include/architecture/mesh.h"

Vector3 getMidPoint3(Vector3 v1, Vector3 v2, Vector3 v3){
    Vector3 midPoint;
    midPoint.x = (v1.x + v2.x + v3.x) / 3;
    midPoint.y = (v1.y + v2.y + v3.y) / 3;
    midPoint.z = (v1.z + v2.z + v3.z) / 3;
    return midPoint;
}

int getClosestTriangle(Vector3* minPoints, Vector3* maxPoints, int* ids, int curr, int count){
    float closestDistance = INFINITY;
    int closest = curr;
    Vector3 midCurr = midPoint(minPoints[curr], maxPoints[curr]);
    for(int i = 0; i < count; i++){
        if(i == curr || ids[i] == -1) continue;
        float distance = dist(midPoint(minPoints[i], maxPoints[i]), midCurr);
        if(distance < closestDistance){
            closestDistance = distance;
            closest = i;
        }
    }
    return closest;
}

// ids contains the ids of the bbox assiocated with the midpoints
void buildLayer(Vector3* minPoints, Vector3* maxPoints, int* ids, int count, Mesh* mesh, int isBottomLayer){
    printf("layer of %d\n", count);
    Vector3 newMinPoints[count / 2 + count%2];
    Vector3 newMaxPoints[count / 2 + count%2];
    int newIds[count/2];
    int newCurrent = 0;

    for(int i = 0; i < count; i ++){
        if(ids[i] == -1) continue;
        int closest = getClosestTriangle(minPoints, maxPoints, ids, i, count);
        int curBbox = mesh->bboxCount;
        if(i != closest){
            mesh->maxBbox[curBbox] = maxv3(maxPoints[i], maxPoints[closest]);
            mesh->minBbox[curBbox] = minv3(minPoints[i], minPoints[closest]);
            mesh->children[curBbox].y = isBottomLayer ? -ids[closest] : ids[closest];
            mesh->children[curBbox].x = isBottomLayer ? -ids[i] : ids[i];

            newMaxPoints[newCurrent] = mesh->maxBbox[curBbox];
            newMinPoints[newCurrent] = mesh->minBbox[curBbox];
            newIds[newCurrent] = curBbox;

            mesh->bboxCount++;
        }else{
            newMinPoints[newCurrent] = minPoints[i];
            newMaxPoints[newCurrent] = maxPoints[i];
            newIds[newCurrent] = ids[i];
        }
        ids[i] = -1;
        ids[closest] = -1;
        newCurrent++;
    }
    if(count > 1)
        buildLayer(newMinPoints, newMaxPoints, newIds, newCurrent, mesh, 0);                
}

int setupBboxCount(Mesh* mesh){
    int depth = (int) ceil(log2(mesh->triangleCount));
    int bboxCount = pow(2, depth + 1) - 1;
    bboxCount -= pow(2, depth) - mesh->triangleCount;
    printf("bboxCount: %d\n", bboxCount);
    mesh->maxBbox = malloc(sizeof(Vector3) * bboxCount);
    mesh->minBbox = malloc(sizeof(Vector3) * bboxCount);
    mesh->children = malloc(sizeof(int2) * bboxCount);
    mesh->bboxCount = 0;
    return depth;
}

void buildBbox(Mesh* mesh){
    //setup
    int ids[mesh->triangleCount];
    Vector3 minPoints[mesh->triangleCount];
    Vector3 maxPoints[mesh->triangleCount];
    for(int i = 0; i < mesh->triangleCount; i++){
        ids[i] = i+1;
        Triangle t = mesh->triangles[i];
        minPoints[i] = minv3(mesh->vertices[t.vs.x], minv3(mesh->vertices[t.vs.y], mesh->vertices[t.vs.z]));
        maxPoints[i] = maxv3(mesh->vertices[t.vs.x], maxv3(mesh->vertices[t.vs.y], mesh->vertices[t.vs.z]));
    }
    int depth = setupBboxCount(mesh);
    buildLayer(minPoints, maxPoints, ids, mesh->triangleCount, mesh, 1);
}

Mesh* createMesh(char* path, Transform transform) {
    Mesh* mesh = malloc(sizeof(Mesh));
    parseObjFile(path, mesh, &transform);
    buildBbox(mesh);
    printf("Mesh %s created (%d vertices, %d faces)\n", path, mesh->vertexCount, mesh->triangleCount);
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
    free(m);
}

