#include "../../include/acceleration/lod.h"

int findParent(Mesh* mesh, int id){
    for(int i = 0; i < mesh->bboxCount; i++){
        int2 children = mesh->children[i];
        if(children.x == id || children.y == id){
            return i;
        }
    }
    return -1;
}

void findFurthestBbox(Mesh* mesh, int curr, Vector3* camPos, int* maxId, float *maxDist)
{
    int2 children = mesh->children[curr];
    Vector3 middle = add(mesh->maxBbox[curr], mesh->minBbox[curr]);
    middle = scalef(middle, 0.5f);
    float distance = dist(middle, *camPos);
    if(distance > *maxDist && children.x <= 0 && children.y <= 0){
        *maxDist = distance;
        *maxId = curr;
    }
    if(children.x > 0){
        findFurthestBbox(mesh, children.x, camPos, maxId, maxDist);
    }
    if(children.y > 0){
        findFurthestBbox(mesh, children.y, camPos, maxId, maxDist);
    }
}

void simplifyMesh(Mesh* mesh, Vector3 camPos)
{
    int id = 0;
    float distance = 0;
    findFurthestBbox(mesh, 0, &camPos, &id, &distance);
    if(id != 0){
        int parent = findParent(mesh, id);
        int2 children = mesh->children[parent];
        if(children.x == 0 && children.y == 0){
            id = parent;
        }else{
            if(children.x == id){
                mesh->children[parent].x = 0;
            }else{
                mesh->children[parent].y = 0;
            }
            id = 0;
        }
    }
}