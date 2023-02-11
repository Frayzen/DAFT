#include <stdlib.h>
#include <stdio.h>
#pragma once
//id = size_t, point strut (3 flaots), vetr and tri to staitc,


//init_mesh   add_vertex   , add_tria(3 size_t args index ) , 
//
//
//cast function (ray and tri
//


typedef struct point{
	float x;
	float y;
	float z;
	size_t id_p;
}point;
 
typedef struct triangle
{
	size_t id_t;
	size_t vert[3];
	point normal;
}triangle;

typedef struct mesh
{
	size_t id_m;
	point ** vertexes;
	size_t v_size;
    size_t tri_last_level;
    size_t depth;
    size_t no_extra;
	bbox * bounding_box;
}mesh;

typedef struct camera
{
	size_t id_c;
	point pos;
    //vector pointing toward the direction of the camera
    float pitch;
    float yaw;
    //field of view in degree (90 - 120 degrees)
    size_t FOV;

}camera;

typedef struct light
{
	size_t id_l;
	point pos;
	point dir;
	point color;
	float intensity;
    float spread;
}light;

typedef struct ray
{
	size_t id_r;
	point pos;
	point dir;

	int hit;
	point contact;
	triangle **collision;
}ray;

//
typedef struct world
{

    size_t size_c;
    size_t size_l;
    size_t size_m;
    camera ** cameras;
    light ** lights;
    mesh ** meshes;

}world;


//LBBOX  is the max number of children in a bounding box
#define LBBOX 10
typedef struct bbox
{//either children or tris is null
    point min;
    point max;
    size_t total;
    bbox * children;
    triangle * tris;
    size_t c_size;
}bbox;