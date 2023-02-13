#include "../include/obj.h"

void proccess(char* line, int i, int p, int t, int n)
{
	int f = 0;
	while(line[i] != ' ')
	{
		if(line[i] != '/')
		{
			if (f == 0)
				p = line[i];
			if (f == 1)
				t = line[i];
			if (f == 2)
				n = line[i];
		}
		else
		{
			f++;
		}
		i++;
	}
}

void parse(char* path, world* w, float scale)
{
	FILE *file = fopen(path, "r");
	if (file == NULL)
	{
		errx(0, "unable to open file\n");
	}

	size_t vert = 0;
	size_t tri = 0;
	//size_t norm = 0;
	//size_t texture = 0;

	char line[200];

	while (fgets(line, sizeof(line), file))
	{
		if (line[0] == 'v')
		{
			//if (line[1] == 'n')
				//norm++;
			//else if (line[1], 't')
				//texture++;
			//else
			vert++;
		}
		else if (line[0] == 'f')
			tri++;
	}

	mesh *new_mesh = init_mesh(vert, tri, w->size_m);

	fseek(file, 0, SEEK_SET);

	point v;
	while(fgets(line, sizeof(line), file))
	{
		if (line[0] == 'v')
		{
			if (line[1] == ' ')
			{
				sscanf(line, "v %f %f %f", &v.x, &v.y, &v.z);
				v.x *= scale;
				v.y *= scale;
				v.z *= scale;
				add_vertex(new_mesh, 0, v.x, v.y, v.z);
			}
			//line[1] == 'n'
			//line[1] == 't'
		}

		if (line[0] == 'f')
		{
			int p1 = 0, p2 = 0, p3 = 0;
			int t1 = 0, t2 = 0, t3 = 0;
			int n1 = 0, n2 = 0, n3 = 0;
			int f = 0;
			for (int i = 2; line[i] != 0; i++)
			{
				if (line[i] == ' ')
					f++;
				if (f == 1)
					proccess(line, i, p2, t2, n2);
				if (f == 2)
					proccess(line, i, p3, t3, n3);
				if (f == 0)
					proccess(line, i, p1, t1, n1);
			}
			add_tri(new_mesh, new_mesh->t_size, p1, p2, p3);
		}
	}

	fclose(file);
}
