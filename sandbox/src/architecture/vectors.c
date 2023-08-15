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