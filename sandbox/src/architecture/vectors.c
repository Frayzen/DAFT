#include "../../include/architecture/vectors.h"

float dist(Vector3 v1, Vector3 v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}
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
Matrix3 createRotationMatrix(Vector3 rotation){
    Matrix3 result;
    float cosT = cos(rotation.x);
    float sinT = sin(rotation.x);
    float cosB = cos(rotation.y);
    float sinB = sin(rotation.y);
    float cosA = cos(rotation.z);
    float sinA = sin(rotation.z);
    result.r1[0] = cosA * cosB;
    result.r1[1] = cosA * sinB * sinT - sinA * cosT;
    result.r1[2] = cosA * sinB * cosT + sinA * sinT;

    result.r2[0] = sinA * cosB;
    result.r2[1] = sinA * sinB * sinT + cosA * cosT;
    result.r2[2] = sinA * sinB * cosT - cosA * sinT;

    result.r3[0] = -sinB;
    result.r3[1] = cosB * sinT;
    result.r3[2] = cosB * cosT;

    return result;
}

float dot(Vector3 v1, Vector3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
float dot4(Vector4 v1, Vector4 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w;
}
Vector3 cross(Vector3 v1, Vector3 v2) {
    Vector3 result = {v1.y * v2.z - v1.z * v2.y, 
                      v1.z * v2.x - v1.x * v2.z, 
                      v1.x * v2.y - v1.y * v2.x};
    return result;
}

Vector3 multiplyMatrixVector3(Matrix3 m, Vector3 v){
    Vector3 result;
    result.x = m.r1[0] * v.x + m.r1[1] * v.y + m.r1[2] * v.z;
    result.y = m.r2[0] * v.x + m.r2[1] * v.y + m.r2[2] * v.z;
    result.z = m.r3[0] * v.x + m.r3[1] * v.y + m.r3[2] * v.z;
    return result;
}
Vector4 multiplyMatrixVector4(Matrix4 m, Vector4 v){
    Vector4 result;
    result.x = m.r1[0] * v.x + m.r1[1] * v.y + m.r1[2] * v.z + m.r1[3] * v.w;
    result.y = m.r2[0] * v.x + m.r2[1] * v.y + m.r2[2] * v.z + m.r2[3] * v.w;
    result.z = m.r3[0] * v.x + m.r3[1] * v.y + m.r3[2] * v.z + m.r3[3] * v.w;
    result.w = m.r4[0] * v.x + m.r4[1] * v.y + m.r4[2] * v.z + m.r4[3] * v.w;
    return result;
}

Vector4 multiplyMatrixVectTranspose4(Matrix4 m, Vector4 v){
    Vector4 result;
    result.x = m.r1[0] * v.x + m.r2[0] * v.y + m.r3[0] * v.z + m.r4[0] * v.w;
    result.y = m.r1[1] * v.x + m.r2[1] * v.y + m.r3[1] * v.z + m.r4[1] * v.w;
    result.z = m.r1[2] * v.x + m.r2[2] * v.y + m.r3[2] * v.z + m.r4[2] * v.w;
    result.w = m.r1[3] * v.x + m.r2[3] * v.y + m.r3[3] * v.z + m.r4[3] * v.w;
    return result;
}


Vector3 minv3(Vector3 v1, Vector3 v2) {
    Vector3 result = {min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z)};
    return result;
}
Vector3 maxv3(Vector3 v1, Vector3 v2) {
    Vector3 result = {max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z)};
    return result;
}
Vector3 midPoint(Vector3 v1, Vector3 v2) {
    Vector3 result = {(v1.x + v2.x) / 2, (v1.y + v2.y) / 2, (v1.z + v2.z) / 2};
    return result;
}


// Helper function to calculate the determinant of a 3x3 matrix
float determinant3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
    return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

// Function to calculate the inverse of a 4x4 matrix
int inverseMat4(Matrix4* m, Matrix4* r) {
    // Calculate submatrices' determinants
    float detA = determinant3x3(m->r2[1], m->r2[2], m->r2[3], m->r3[1], m->r3[2], m->r3[3], m->r4[1], m->r4[2], m->r4[3]);
    float detB = determinant3x3(m->r2[0], m->r2[2], m->r2[3], m->r3[0], m->r3[2], m->r3[3], m->r4[0], m->r4[2], m->r4[3]);
    float detC = determinant3x3(m->r2[0], m->r2[1], m->r2[3], m->r3[0], m->r3[1], m->r3[3], m->r4[0], m->r4[1], m->r4[3]);
    float detD = determinant3x3(m->r2[0], m->r2[1], m->r2[2], m->r3[0], m->r3[1], m->r3[2], m->r4[0], m->r4[1], m->r4[2]);

    float detM = m->r1[0] * detA - m->r1[1] * detB + m->r1[2] * detC - m->r1[3] * detD;

    if (detM == 0.0) {
        return 0; // Matrix is not invertible
    }

    float invDetM = 1.0 / detM;

    // Calculate inverse matrix elements
    r->r1[0] = detA * invDetM;
    r->r1[1] = -determinant3x3(m->r1[1], m->r1[2], m->r1[3], m->r3[1], m->r3[2], m->r3[3], m->r4[1], m->r4[2], m->r4[3]) * invDetM;
    r->r1[2] = determinant3x3(m->r1[1], m->r1[2], m->r1[3], m->r2[1], m->r2[2], m->r2[3], m->r4[1], m->r4[2], m->r4[3]) * invDetM;
    r->r1[3] = -determinant3x3(m->r1[1], m->r1[2], m->r1[3], m->r2[1], m->r2[2], m->r2[3], m->r3[1], m->r3[2], m->r3[3]) * invDetM;

    r->r2[0] = -determinant3x3(m->r2[0], m->r2[2], m->r2[3], m->r3[0], m->r3[2], m->r3[3], m->r4[0], m->r4[2], m->r4[3]) * invDetM;
    r->r2[1] = determinant3x3(m->r1[0], m->r1[2], m->r1[3], m->r3[0], m->r3[2], m->r3[3], m->r4[0], m->r4[2], m->r4[3]) * invDetM;
    r->r2[2] = -determinant3x3(m->r1[0], m->r1[2], m->r1[3], m->r2[0], m->r2[2], m->r2[3], m->r4[0], m->r4[2], m->r4[3]) * invDetM;
    r->r2[3] = determinant3x3(m->r1[0], m->r1[2], m->r1[3], m->r2[0], m->r2[2], m->r2[3], m->r3[0], m->r3[2], m->r3[3]) * invDetM;

    r->r3[0] = determinant3x3(m->r2[0], m->r2[1], m->r2[3], m->r3[0], m->r3[1], m->r3[3], m->r4[0], m->r4[1], m->r4[3]) * invDetM;
    r->r3[1] = -determinant3x3(m->r1[0], m->r1[1], m->r1[3], m->r3[0], m->r3[1], m->r3[3], m->r4[0], m->r4[1], m->r4[3]) * invDetM;
    r->r3[2] = determinant3x3(m->r1[0], m->r1[1], m->r1[3], m->r2[0], m->r2[1], m->r2[3], m->r4[0], m->r4[1], m->r4[3]) * invDetM;
    r->r3[3] = -determinant3x3(m->r1[0], m->r1[1], m->r1[3], m->r2[0], m->r2[1], m->r2[3], m->r3[0], m->r3[1], m->r3[3]) * invDetM;

    r->r4[0] = -determinant3x3(m->r2[0], m->r2[1], m->r2[2], m->r3[0], m->r3[1], m->r3[2], m->r4[0], m->r4[1], m->r4[2]) * invDetM;
    r->r4[1] = determinant3x3(m->r1[0], m->r1[1], m->r1[2], m->r3[0], m->r3[1], m->r3[2], m->r4[0], m->r4[1], m->r4[2]) * invDetM;
    r->r4[2] = -determinant3x3(m->r1[0], m->r1[1], m->r1[2], m->r2[0], m->r2[1], m->r2[2], m->r4[0], m->r4[1], m->r4[2]) * invDetM;
    r->r4[3] = determinant3x3(m->r1[0], m->r1[1], m->r1[2], m->r2[0], m->r2[1], m->r2[2], m->r3[0], m->r3[1], m->r3[2]) * invDetM;

    return 1; // Matrix inversion successful
}