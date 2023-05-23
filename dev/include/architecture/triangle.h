#include <stdlib.h>
#include "./material.h"
#ifndef TRIANGLE_H
#define TRIANGLE_H
typedef struct triangle
{
	int v[3];
	int vn[3];
	int vt[3];
        material* material;
}triangle;
#endif
