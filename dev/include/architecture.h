#include <stdlib.h>
#include <stdio.h>




typedef struct triangle
{
	int id_t;
	size_t points[3];
	float normal[0];
}triangle;

typedef struct mesh
{
	int id_m;
	float **vertexs;
	size_t v_size;
	size_t t_size;
	triangle ** triangles;
}mesh;

typedef struct camera
{
	float pos[3];
	float dir[3];
}camera;

typedef struct light
{
	float pos[3];
	float dir[3];
	float color[3];
	float intensity;
}light;

typedef struct ray
{
	float pos[3];
	float dir[3];

	int hit;
	float contact[3];
	triangle **collision;
}ray;


typedef struct world
{
	mesh ** objects;
	camera ** cameras;
	light ** lights;
}world;





