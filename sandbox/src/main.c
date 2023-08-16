#include "../include/architecture/world.h"
#include "../include/architecture/transform.h"
#include "../include/window/window.h"
#include "../include/architecture/mesh.h"

int main(int argc, char *argv[]){
	DaftApp* app = initApp();
	app->camera = createCamera();
	app->camera->position = (Vector3){-2, 0, 0};
	worldAddMesh(app->world, createMesh("./assets/objs/teddy.obj", createTransformS((Vector3){.1,.1,.1})));
	worldSetSkybox(app->world, "./assets/skybox/Sky.jpg");
	launchApp(app);
	freeApp(app);
	return 0;
}