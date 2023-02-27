#include "../include/utils.h"
#include "../include/bbox.h"
#define MAX_CAM 5
#define MAX_LIGHT 5
#define MAX_MESH 5
#define MAX_RAY 100


float min(float x, float y){
    return x < y ? x : y;
}
float max(float x, float y){
    return x > y ? x : y;
}
camera * init_camera(size_t id, point pos, float pitch, float yaw, int FOV)
    {
	camera * cam = (camera *)malloc(sizeof(camera));
	cam->id_c = id;
	cam->pos = pos;
    cam->pitch = pitch;
    cam->yaw = yaw;
    cam->FOV = FOV;
    cam->skybox = NULL;
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


ray * init_ray(point pos, point dir)
{
	ray * r = (ray *)malloc(sizeof(ray));
	r->pos = pos;
	r->dir = dir;
	r->hit = 0;
    r->c.r = 0;
    r->c.g = 0;
    r->c.b = 0;
    r->mint = -1;
	return r;
}




triangle *  init_triangle(size_t x, size_t y, size_t z)
{
	triangle * t = malloc(sizeof(triangle));
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
point copyp(point p){
    point r;
    r.x = p.x;
    r.y = p.y;
    r.z = p.z;
    return r;
}
point * init_point(float x, float y, float z)
{
	point * p = (point *)malloc(sizeof(point));
	p->x = x;
	p->y = y;
	p->z = z;
	return p;
}



mesh * init_mesh(size_t no_vert, size_t no_tri, size_t id)
{

    mesh * m = (mesh *)malloc(sizeof(mesh));
    m->depth = compute_depth(no_tri-1);
    m->tri_last_level = compute_tri_last_level(m->depth, no_tri);
    m->no_extra = compute_no_extra(no_tri, m->tri_last_level, m->depth);
    m->bounding_box = build_bbox(m->depth, m->tri_last_level, m->no_extra);
	m->id_m = id;
	m->v_size = 0;
	m->vertexes = malloc(sizeof(point)*no_vert);

	return m;
}


void add_vertex(mesh * m, float x, float y, float z)
{
	m->vertexes[m->v_size] = npoint(x,y,z);
	m->v_size++;
}

void get_vertex_from_triangle(mesh* m, triangle* tri, point* a, point* b, point *c){
    *a = m->vertexes[tri->vert[0]];
    *b = m->vertexes[tri->vert[1]];
    *c = m->vertexes[tri->vert[2]];
}


void add_tri(mesh * m, size_t a, size_t b, size_t c)
{
		triangle* t = init_triangle(a, b, c);
        add_tri_to_bbox(m, m->bounding_box, m->depth, t);
}


void free_mesh(mesh * m)
{
	if(m->vertexes != NULL)
		free(m->vertexes);
    free_bbox(m->bounding_box);
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
            if(w->cameras[i]->skybox)
                SDL_FreeSurface(w->cameras[i]->skybox);
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
    float sum = norm(p);
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
float norm(point p){
    return sqrtf(p.x*p.x+p.y*p.y+p.z*p.z);
}
