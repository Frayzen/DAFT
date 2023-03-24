#include <stdlib.h>
#ifndef TRIANGLE_H
#define TRIANGLE_H
typedef struct triangle
{
	int vert[3];
	float normal[3];
}triangle;
triangle* init_triangle(int a, int b, int c);
#endif