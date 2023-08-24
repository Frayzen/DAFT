#include "../../include/acceleration/lod.h"

int findParent(Mesh *mesh, int id)
{
    for (int i = 0; i < mesh->bboxCount; i++)
    {
        int2 children = mesh->children[i];
        if (children.x == id || children.y == id)
        {
            return i;
        }
    }
    return -1;
}

void findFurthestBbox(Mesh *mesh, int curr, Vector3 *camPos, int *maxId, float *maxDist)
{
    int2 children = mesh->children[curr];
    Vector3 middle = add(mesh->maxBbox[curr], mesh->minBbox[curr]);
    middle = scalef(middle, 0.5f);
    float distance = dist(middle, *camPos);
    if (distance < *maxDist && children.x <= 0 && children.y <= 0)
    {
        *maxDist = distance;
        *maxId = curr;
    }
    if (children.x > 0)
    {
        findFurthestBbox(mesh, children.x, camPos, maxId, maxDist);
    }
    if (children.y > 0)
    {
        findFurthestBbox(mesh, children.y, camPos, maxId, maxDist);
    }
}

int2 findCommonPoints(Triangle t1, Triangle t2)
{
    int2 commonIds = {-1, -1};
    if (t1.vs.x == t2.vs.x || t1.vs.x == t2.vs.y || t1.vs.x == t2.vs.z)
    {
        commonIds.x = t1.vs.x;
    }
    if (t1.vs.y == t2.vs.x || t1.vs.y == t2.vs.y || t1.vs.y == t2.vs.z)
    {
        if (commonIds.x == -1)
        {
            commonIds.x = t1.vs.y;
        }
        else
        {
            commonIds.y = t1.vs.y;
            return commonIds;
        }
    }
    if (t1.vs.z == t2.vs.x || t1.vs.z == t2.vs.y || t1.vs.z == t2.vs.z)
    {
        commonIds.y = t1.vs.z;
    }
    return commonIds;
}

#define MAX_VECTOR3 \
    (Vector3) { INFINITY, INFINITY, INFINITY }
#define MIN_VECTOR3 \
    (Vector3) { -INFINITY, -INFINITY, -INFINITY }
void rebuildBboxesBounds(Mesh *mesh, int curr)
{
    int2 children = mesh->children[curr];
    Vector3 leftMax, leftMin, rightMax, rightMin;
    if(children.x == 0 && children.y == 0){
        return;
    }
    if (children.x < 0)
    {
        Triangle t = mesh->triangles[-(children.x + 1)];
        leftMax = maxv3(mesh->vertices[t.vs.x], maxv3(mesh->vertices[t.vs.y], mesh->vertices[t.vs.z]));
        leftMin = minv3(mesh->vertices[t.vs.x], minv3(mesh->vertices[t.vs.y], mesh->vertices[t.vs.z]));
    }
    else if (children.x != 0)
    {
        rebuildBboxesBounds(mesh, children.x);
        leftMax = mesh->maxBbox[children.x];
        leftMin = mesh->minBbox[children.x];
    }
    else
    {
        leftMax = MIN_VECTOR3;
        leftMin = MAX_VECTOR3;
    }
    if (children.y < 0)
    {
        Triangle t = mesh->triangles[-(children.y + 1)];
        rightMax = maxv3(mesh->vertices[t.vs.x], maxv3(mesh->vertices[t.vs.y], mesh->vertices[t.vs.z]));
        rightMin = minv3(mesh->vertices[t.vs.x], minv3(mesh->vertices[t.vs.y], mesh->vertices[t.vs.z]));
    }
    else if (children.y != 0)
    {
        rebuildBboxesBounds(mesh, children.y);
        rightMax = mesh->maxBbox[children.y];
        rightMin = mesh->minBbox[children.y];
    }
    else
    {
        rightMax = MIN_VECTOR3;
        rightMin = MAX_VECTOR3;
    }
    mesh->maxBbox[curr] = maxv3(leftMax, rightMax);
    mesh->minBbox[curr] = minv3(leftMin, rightMin);
}

void replaceVerticle(Mesh *mesh, int oldId, int newId)
{
    for (int i = 0; i < mesh->triangleCount; i++)
    {
        Triangle t = mesh->triangles[i];
        if (t.vs.x == oldId)
        {
            mesh->triangles[i].vs.x = newId;
        }
        if (t.vs.y == oldId)
        {
            mesh->triangles[i].vs.y = newId;
        }
        if (t.vs.z == oldId)
        {
            mesh->triangles[i].vs.z = newId;
        }
    }
}

void simplifyMesh(Mesh *mesh, Vector3 camPos)
{
    int id = 0;
    float distance = INFINITY;
    findFurthestBbox(mesh, 0, &camPos, &id, &distance);
    int loopId = id;
    while (loopId != 0)
    {
        int parent = findParent(mesh, loopId);
        int2 children = mesh->children[parent];
        if (children.x == loopId)
        {
            mesh->children[parent].x = 0;
            if (children.y != 0)
                loopId = 0;
            else
                loopId = parent;
        }
        else
        {
            mesh->children[parent].y = 0;
            if (children.x != 0)
                loopId = 0;
            else
                loopId = parent;
        }
    }

    int2 tris = mesh->children[id];
    if(tris.x == 0 || tris.y == 0){
        int triId = tris.x == 0 ? tris.y : tris.x;
        if(triId == 0){
            return;
        }
        Triangle t = mesh->triangles[-(triId + 1)];
        Vector3 middle = add(mesh->vertices[t.vs.x], add(mesh->vertices[t.vs.y], mesh->vertices[t.vs.z]));
        middle = scalef(middle, 1.0f / 3.0f);
        mesh->vertices[t.vs.x] = middle;
        mesh->vertices[t.vs.y] = middle;
        mesh->vertices[t.vs.z] = middle;
        replaceVerticle(mesh, t.vs.y, t.vs.x);
        replaceVerticle(mesh, t.vs.z, t.vs.x);
        return;
    }
    Triangle t1 = mesh->triangles[-(tris.x + 1)];
    Triangle t2 = mesh->triangles[-(tris.y + 1)];
    int2 commonIds = findCommonPoints(t1, t2);
    if (commonIds.x != -1 && commonIds.y != -1)
    {
        Vector3 middle = add(mesh->vertices[commonIds.x], mesh->vertices[commonIds.y]);
        middle = scalef(middle, 0.5f);
        mesh->vertices[commonIds.x] = middle;
        mesh->vertices[commonIds.y] = middle;
        replaceVerticle(mesh, commonIds.x, commonIds.y);
        rebuildBboxesBounds(mesh, 0);
    }
}