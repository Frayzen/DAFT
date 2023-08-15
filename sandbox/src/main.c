#include "../include/architecture/world.h"
#include "../include/architecture/mesh.h"

int main(int argc, char *argv[]){
	World* w = createWorld();
	Mesh* m = createMesh("./assets/objs/cube.obj");
	worldAddMesh(w, m);
	freeWorld(w);
	return 0;
}