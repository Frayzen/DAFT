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
Vector3 scalef(Vector3 v, float s) {
    v.x = v.x * s;
    v.y = v.y * s;
    v.z = v.z * s;
    return v;
}

Vector3 scale(Vector3 v1, Vector3 v2) {
    Vector3 result = {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
    return result;
}

Vector3 rotate(Vector3 v, Vector3 rotation) {
    Vector3 result = {0, 0, 0};
    float x = v.x;
    float y = v.y;
    float z = v.z;
    float cosX = cos(rotation.x);
    float sinX = sin(rotation.x);
    float cosY = cos(rotation.y);
    float sinY = sin(rotation.y);
    float cosZ = cos(rotation.z);
    float sinZ = sin(rotation.z);
    result.x = x * cosY * cosZ + y * (cosZ * sinX * sinY - cosX * sinZ) + z * (cosX * cosZ * sinY + sinX * sinZ);
    result.y = x * cosY * sinZ + y * (cosX * cosZ + sinX * sinY * sinZ) + z * (cosX * sinY * sinZ - cosZ * sinX);
    result.z = -x * sinY + y * cosY * sinX + z * cosX * cosY;
    return result;
}

Vector3 rotateRPY(Vector3 v, Vector3 rpy){
    float roll = rpy.x;
    float pitch = rpy.y;
    float yaw = rpy.z;
    float cosRoll = cos(roll);
    float sinRoll = sin(roll);
    float cosPitch = cos(pitch);
    float sinPitch = sin(pitch);
    float cosYaw = cos(yaw);
    float sinYaw = sin(yaw);
    Vector3 result = {0, 0, 0};
    result.x = v.x * cosPitch * cosYaw + v.y * (cosYaw * sinPitch * sinRoll - cosRoll * sinYaw) + v.z * (cosRoll * cosYaw * sinPitch + sinRoll * sinYaw);
    result.y = v.x * cosPitch * sinYaw + v.y * (cosRoll * cosYaw + sinPitch * sinRoll * sinYaw) + v.z * (cosRoll * sinPitch * sinYaw - cosYaw * sinRoll);
    result.z = -v.x * sinPitch + v.y * cosPitch * sinRoll + v.z * cosRoll * cosPitch;
    return result;
}
Matrix createRotationMatrix(Vector3 rotation){
    Matrix result;
    float cosX = cos(rotation.x);
    float sinX = sin(rotation.x);
    float cosY = cos(rotation.y);
    float sinY = sin(rotation.y);
    float cosZ = cos(rotation.z);
    float sinZ = sin(rotation.z);
    result.c1[0] = cosY * cosZ;
    result.c1[1] = cosZ * sinX * sinY - cosX * sinZ;
    result.c1[2] = cosX * cosZ * sinY + sinX * sinZ;
    result.c2[0] = cosY * sinZ;
    result.c2[1] = cosX * cosZ + sinX * sinY * sinZ;
    result.c2[2] = cosX * sinY * sinZ - cosZ * sinX;
    result.c3[0] = -sinY;
    result.c3[1] = cosY * sinX;
    result.c3[2] = cosX * cosY;
    return result;
}
Vector3 multiplyMatrixVector(Matrix m, Vector3 v){
    Vector3 result;
    result.x = m.c1[0] * v.x + m.c1[1] * v.y + m.c1[2] * v.z;
    result.y = m.c2[0] * v.x + m.c2[1] * v.y + m.c2[2] * v.z;
    result.z = m.c3[0] * v.x + m.c3[1] * v.y + m.c3[2] * v.z;
    return result;
}