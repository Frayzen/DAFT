#include "../../include/architecture/triangle.h"

triangle* init_triangle(int a, int b, int c)
{
    triangle* t = malloc(sizeof(triangle));
    t->vert[0] = a;
    t->vert[1] = b;
    t->vert[2] = c;
    return t;
}