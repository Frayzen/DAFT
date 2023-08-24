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
    if (distance < *maxDist && children.x < 0 && children.y < 0)
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

#define MAX_VECTOR3 (Vector3){INFINITY, INFINITY, INFINITY}
#define MIN_VECTOR3 (Vector3){-INFINITY, -INFINITY, -INFINITY}
void rebuildBboxesBounds(Mesh *mesh, int curr)
{
    int2 children = mesh->children[curr];
    Vector3 leftMax, leftMin, rightMax, rightMin;
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
        leftMax = MAX_VECTOR3;
        leftMin = MIN_VECTOR3;
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
        rightMax = MAX_VECTOR3;
        rightMin = MIN_VECTOR3;
    }
    mesh->maxBbox[curr] = maxv3(leftMax, rightMax);
    mesh->minBbox[curr] = minv3(leftMin, rightMin);
}

void simplifyMesh(Mesh *mesh, Vector3 camPos)
{
    int id = 0;
    float distance = INFINITY;
    findFurthestBbox(mesh, 0, &camPos, &id, &distance);
    int2 tris = mesh->children[id];
    Triangle t1 = mesh->triangles[-(tris.x + 1)];
    Triangle t2 = mesh->triangles[-(tris.y + 1)];
    int2 commonIds = findCommonPoints(t1, t2);

    
    if (commonIds.x != -1 && commonIds.y != -1)
    {
        Vector3 middle = add(mesh->vertices[commonIds.x], mesh->vertices[commonIds.y]);
        middle = scalef(middle, 0.5f);
        mesh->vertices[commonIds.x] = middle;
        mesh->vertices[commonIds.y] = middle;
        rebuildBboxesBounds(mesh, 0);
    }
}