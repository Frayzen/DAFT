#include "../../include/acceleration/rasterization.h"

Vector2 minv2(Vector2 v1, Vector2 v2){
    Vector2 result = {min(v1.x, v2.x), min(v1.y, v2.y)};
    return result;
}

Vector2 maxv2(Vector2 v1, Vector2 v2){
    Vector2 result = {max(v1.x, v2.x), max(v1.y, v2.y)};
    return result;
}

void rasterizeBbox(Mesh* m, Camera* cam, int* result){
    Vector3 min = m->minBbox[0];
    Vector3 max = m->maxBbox[0];
    Matrix4 projectionMatrix = getProjectionMatrix(cam);
    Vector3 projectedMin = normalize(vect4to3(multiplyMatrixVector4(projectionMatrix, vect3to4(min))));
    Vector3 projectedMax = normalize(vect4to3(multiplyMatrixVector4(projectionMatrix, vect3to4(max))));
    
    float longitudeMin = atan(projectedMin.z / projectedMin.x);
    float longitudeMax = atan(projectedMax.z / projectedMax.x);
    float latitudeMin = atan(projectedMin.z/sqrt(pow(projectedMin.x, 2) + pow(projectedMin.y, 2)));
    float latitudeMax = atan(projectedMax.z/sqrt(pow(projectedMax.x, 2) + pow(projectedMax.y, 2)));

    int xMin = (longitudeMin + M_PI) / (2 * M_PI) * SCREEN_WIDTH;
    int xMax = (longitudeMax + M_PI) / (2 * M_PI) * SCREEN_WIDTH;
    int yMin = (latitudeMin + M_PI / 2) / M_PI * SCREEN_HEIGHT;
    int yMax = (latitudeMax + M_PI / 2) / M_PI * SCREEN_HEIGHT;
    memset(result, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int));

    xMin = 100;
    xMax = 200;
    yMin = 100;
    yMax = 200;

    for (int y = yMin; y < yMax; y++)
    {
        memset(result + y * SCREEN_WIDTH + xMin, 1, (xMax - xMin) * sizeof(int));
    }
}