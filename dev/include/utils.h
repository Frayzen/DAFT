#include "../include/architecture.h"

#pragma once

mesh * init_mesh(int id_m) //not sure if should take noumber of ver and tris as argument
{
	mesh * m = malloc(sizeof(mesh));
	m->id_m = id_m;
	m->vertexs = NULL;
	m->triangles = NULL;
	m->v_size = 0;
	m->t_size = 0;
	return m;
}

void free_mesh(mesh * m)
{
	for(size_t i = 0; i < m->v_size; i++)
		free(m->vertexs[i]);
	for(size_t j = 0; j < m->t_size; j++)
		free(m->triangles[j]);
	free(m);
}


	
