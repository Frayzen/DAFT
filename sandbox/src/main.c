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
	worldSetSkybox(app->world, "./assets/skybox/Sky.jpg");
	launchApp(app);
	freeApp(app);
	return 0;
}