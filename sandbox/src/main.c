#include "../include/architecture/world.h"
#include "../include/window/window.h"
#include "../include/architecture/mesh.h"

int main(int argc, char *argv[]){
	DaftApp* app = initApp();
	app->camera = createCamera();
	worldAddMesh(app->world, createMesh("./assets/objs/cube.obj"));
	worldSetSkybox(app->world, "./assets/skybox/Sky.jpg");
	launchScreen(app);
	freeApp(app);
	return 0;
}