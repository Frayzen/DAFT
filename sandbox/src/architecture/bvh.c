#include "../../include/architecture/bvh.h"

/*
The bbox is built by layer, starting from the bottom layer.
The bottom layer is the triangles of the mesh.
The next layer is built by finding the closest triangles and merging them.
This is done until there is only one bbox left.
*/

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
    Vector3 newMinPoints[count / 2 + count%2];
    Vector3 newMaxPoints[count / 2 + count%2];
    int newIds[count/2];
    int newCurrent = 0;
    
    for(int i = 0; i < count; i ++){
        if(ids[i] == -1) continue;
        int closest = getClosestTriangle(minPoints, maxPoints, ids, i, count);
        int curBbox = count == 2 ? 0 : mesh->bboxCount;
        if(i != closest){
            mesh->maxBbox[curBbox] = maxv3(maxPoints[i], maxPoints[closest]);
            mesh->minBbox[curBbox] = minv3(minPoints[i], minPoints[closest]);
            mesh->children[curBbox].y = isBottomLayer ? -ids[closest] : ids[closest];
            mesh->children[curBbox].x = isBottomLayer ? -ids[i] : ids[i];

            newMaxPoints[newCurrent] = mesh->maxBbox[curBbox];
            newMinPoints[newCurrent] = mesh->minBbox[curBbox];
            newIds[newCurrent] = curBbox;
            if(count != 2)
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

void setupBboxCount(Mesh* mesh){
    int bboxCount = mesh->triangleCount-1;
    mesh->maxBbox = malloc(sizeof(Vector3) * bboxCount);
    mesh->minBbox = malloc(sizeof(Vector3) * bboxCount);
    mesh->children = malloc(sizeof(int2) * bboxCount);
    mesh->bboxCount = 1;
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
    setupBboxCount(mesh);
    buildLayer(minPoints, maxPoints, ids, mesh->triangleCount, mesh, 1);
}