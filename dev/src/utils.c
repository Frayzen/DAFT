#include "../include/utils.h"
#define MAX_CAM 5
#define MAX_LIGHT 5
#define MAX_MESH 5
#define MAX_TRI 75
#define MAX_VERT 75
#define MAX_RAY 100


camera * init_camera(size_t id, point pos, float pitch, float yaw, int FOV)
    {
	camera * cam = (camera *)malloc(sizeof(camera));
	cam->id_c = id;
	cam->pos = pos;
    cam->pitch = pitch;
    cam->yaw = yaw;
    cam->FOV = FOV;
	return cam;
}

void add_camera(world * w, camera * cam)
{
	if(w->cameras == NULL)
	{
		w->cameras =(camera **) malloc(sizeof(camera *) * MAX_CAM);
		w->cameras[0] = cam;
		w->size_c = 1;
	}
	else if (w->size_c < MAX_CAM)
	{
		w->cameras[w->size_c] = cam;
		w->size_c++;
	}
	else
	{
		printf("Error: Max number of cameras reached");
	}

}


light * init_light(size_t id, point pos, point dir, point color, float intensity)
{
	light * l = (light *)malloc(sizeof(light));
	l->id_l = id;
	l->pos = pos;
	l->dir = dir;
	l->color = color;
	l->intensity = intensity;
	return l;
}

void add_light(world * w, light * l)
{
	if (w->size_l < MAX_LIGHT)
	{
		w->lights[w->size_l] = l;
		w->size_l++;
	}
	else
	{
		printf("Error: Max number of lights reached");
	}

}


ray * init_ray(size_t id, point pos, point dir)
{
	ray * r = (ray *)malloc(sizeof(ray));
	r->id_r = id;
	r->pos = pos;
	r->dir = dir;
	r->hit = 0;
	return r;
}




triangle *  init_triangle(size_t id, size_t x, size_t y, size_t z)
{
	triangle * t = (triangle *)malloc(sizeof(triangle) * MAX_TRI);
	t->id_t = id;
	t->vert[0] = x;
	t->vert[1] = y;
	t->vert[2] = z;
	return t;
}

//create a new point
point npoint(float x, float y, float z){
    point p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}
point * init_point(size_t id, float x, float y, float z)
{
	point * p = (point *)malloc(sizeof(point));
	p->x = x;
	p->y = y;
	p->z = z;
	p->id_p = id;
	return p;
}



mesh * init_mesh(size_t no_vert, size_t no_tri, size_t id)
{
	mesh * m = (mesh *)malloc(sizeof(mesh));
	m->id_m = id;
	m->t_size = 0;
	m->v_size = 0;
	m->triangles = (triangle **)malloc(sizeof(triangle*)*no_tri);
	m->vertexes = (point **)malloc(sizeof(point *)*no_vert);
	return m;
}


void add_vertex(mesh * m, size_t id, float x, float y, float z)
{
	if (m->v_size < MAX_VERT)
	{
		point * p = init_point(id, x, y, z);
		m->vertexes[m->v_size] = p;
		m->v_size++;
	}

}

void add_tri(mesh * m, size_t id, size_t a, size_t b, size_t c)
{
	if (m->t_size < MAX_TRI)
	{
		triangle *  t = init_triangle(id, a, b, c);
		m->triangles[m->t_size] = t;
		m->t_size++;
	}
}


void free_mesh(mesh * m)
{
	if(m->triangles != NULL)
	{
		for(size_t i = 0; i < m->t_size; i++)
		{
			free(m->triangles[i]);
		}
		free(m->triangles);
	}
	if(m->vertexes != NULL)
	{
		for(size_t i = 0; i < m->v_size; i++)
		{
			free(m->vertexes[i]);
		}
		free(m->vertexes);
	}
	free(m);
}

world * init_world()
{
	world * w =(world *) malloc(sizeof(world));
	w->meshes = (mesh **)malloc(sizeof(mesh)*(MAX_MESH));
	w->cameras =(camera **) malloc(sizeof(camera)*(MAX_CAM));
	w->lights = (light **)malloc(sizeof(light)*(MAX_LIGHT));

	w->size_c = 0;
	w->size_l = 0;
	w->size_m = 0;

	return w;
}

void add_mesh(world * w, mesh * m)
{
	if (w->size_m < MAX_MESH)
	{
		w->meshes[w->size_m] = m;
		w->size_m++;
	}
	else
	{
		printf("Error: Max number of meshes reached");
	}

}

void free_world(world * w)
{
	if(w->meshes != NULL)
	{
		for(size_t i = 0; i < w->size_m; i++)
		{
			free_mesh(w->meshes[i]);
		}
		free(w->meshes);
	}
	if(w->cameras != NULL)
	{
		for(size_t i = 0; i < w->size_c; i++)
		{
			free(w->cameras[i]);
		}
		free(w->cameras);
	}
	if(w->lights != NULL)
	{
		for(size_t i = 0; i < w->size_l; i++)
		{
			free(w->lights[i]);
		}
		free(w->lights);
	}
	free(w);
}

float dot(point  a, point  b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

 point crossProduct(point a, point b)
 {
        point c;
        c.x = a.y*b.z - a.z*b.y;
        c.y = a.z*b.x - a.x*b.z;
        c.z = a.x*b.y - a.y*b.x;
        return c;
 }


point scale(point a, float s){
    a.x*=s;
    a.y*=s;
    a.z*=s;
    return a;
}
void scalep(point * a, float s)
{
    a->x *= s;
    a->y *= s;
    a->z *= s;
}
point add(point a, point b){
    a.x+=b.x;
    a.y+=b.y;
    a.z+=b.z;
    return a;
}
void addp(point * a, point * b)
{
    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
}
point minus(point a, point b){
    a.x-=b.x;
    a.y-=b.y;
    a.z-=b.z;
    return a;
}
void minusp(point * a, point * b)
{
    a->x -= b->x;
    a->y -= b->y;
    a->z -= b->z;
}

point normalize(point p){
    float sum = p.x+p.y+p.z;
    if(sum == 0)
        return p;
    p.x/=sum;
    p.y/=sum;
    p.z/=sum;
    return p;
}
void ppoint(point p, char* msg){
    printf("POINT %s %f %f %f\n", msg, p.x, p.y, p.z);
}
