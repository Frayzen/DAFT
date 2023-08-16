#include "../../include/architecture/transform.h"

Transform createTransformPRS(Vector3 position, Vector3 rotation, Vector3 scale) {
    Transform t = {position, rotation, scale};
    return t;
}

Transform createTransformPR(Vector3 position, Vector3 rotation) {
    Transform t = {position, rotation, (Vector3){1, 1, 1}};
    return t;
}

Transform createTransformPS(Vector3 position, Vector3 scale) {
    Transform t = {position, (Vector3){0, 0, 0}, scale};
    return t;
}

Transform createTransformP(Vector3 position) {
    Transform t = {position, (Vector3){0, 0, 0}, (Vector3){1, 1, 1}};
    return t;
}

Transform createTransformS(Vector3 scale) {
    Transform t = {(Vector3){0, 0, 0}, (Vector3){0, 0, 0}, scale};
    return t;
}

Transform createTransformR(Vector3 rotation) {
    Transform t = {(Vector3){0, 0, 0}, rotation, (Vector3){1, 1, 1}};
    return t;
}

Transform createTransform() {
    Transform t = {(Vector3){0, 0, 0}, (Vector3){0, 0, 0}, (Vector3){1, 1, 1}};
    return t;
}

Vector3 transformVector3(Vector3 v, Transform* t) {
    Vector3 r = rotate(v, t->rotation);
    Vector3 s = scale(r, t->scale);
    Vector3 p = add(s, t->position);
    return p;
}