#include "../include/architecture/world.h"
#include "../include/window/window.h"
#include "../include/architecture/mesh.h"

int main(int argc, char *argv[]){
	DaftApp* app = initApp();
	app->camera = createCamera();
	app->camera->position = (Vector3){-4, 0, 0};
	worldAddMesh(app->world, createMesh("./assets/objs/cube.obj"));
	worldSetSkybox(app->world, "./assets/skybox/Factory.jpg");
	launchApp(app);
	freeApp(app);
	return 0;
}