#include "architecture.h"
#pragma once
#define MAX_CAM 5
#define MAX_LIGHT 5
#define MAX_MESH 5
#define MAX_TRI 75
#define MAX_VERT 75

camera * init_camera(size_t id, point pos, point dir);

void add_camera(world * w, camera * cam);

light * init_light(size_t id, point pos, point dir, point color, float intensity);

void add_light(world * w, light * l);

ray * init_ray(size_t id, point pos, point dir);

triangle *  init_triangle(size_t id, size_t x, size_t y, size_t z);

point * init_point(size_t id, float x, float y, float z);

mesh * init_mesh(size_t no_vert, size_t no_tri, size_t id);

void add_vertex(mesh * m, size_t id, float x, float y, float z);

void add_tri(mesh * m, size_t id, size_t a, size_t b, size_t c);

void free_mesh(mesh * m);
world * init_world();

void add_mesh(world * w, mesh * m);

void free_world(world * w);

