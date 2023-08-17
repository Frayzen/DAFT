#include "../include/architecture/world.h"
#include "../include/architecture/transform.h"
#include "../include/window/window.h"
#include "../include/architecture/mesh.h"

int main(int argc, char *argv[]){
	DaftApp* app = initApp();
	app->camera = createCamera();
	app->camera->position = (Vector3){0, 0, -1};
	//worldAddMesh(app->world, createMesh("./assets/objs/teddy.obj", createTransformS((Vector3){.01,.01,.01})));
	worldAddMesh(app->world, createMesh("./assets/objs/cube.obj", createTransform()));
	Mesh* m = app->world->meshes[0];
	printf("bboxcount: %d\n", m->bboxCount);
	for (int i = 0; i < m->bboxCount; i++)
	{
		printf("========== %d\n", i);
		printf("max: %f %f %f\n", m->maxBbox[i].x, m->maxBbox[i].y, m->maxBbox[i].z);
		printf("min: %f %f %f\n", m->minBbox[i].x, m->minBbox[i].y, m->minBbox[i].z);
		printf("children: %d %d\n", m->children[i].x, m->children[i].y);
	}
	
	
	worldSetSkybox(app->world, "./assets/skybox/Sky.jpg");
	launchApp(app);
	freeApp(app);
	return 0;
}