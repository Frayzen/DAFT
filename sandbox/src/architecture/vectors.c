#include "../../include/architecture/vectors.h"

Vector2 normalize2(Vector2 v) {
    float length = sqrt(v.x * v.x + v.y * v.y);
    Vector2 result = {v.x / length, v.y / length};
    return result;
}
Vector3 normalize(Vector3 v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    Vector3 result = {v.x / length, v.y / length, v.z / length};
    return result;
}
Vector3 add(Vector3 v1, Vector3 v2) {
    Vector3 result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return result;
}
Vector3 sub(Vector3 v1, Vector3 v2) {
    Vector3 result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return result;
}
Vector3 scale(Vector3 v, float s) {
    v.x = v.x * s;
    v.y = v.y * s;
    v.z = v.z * s;
    return v;
}
