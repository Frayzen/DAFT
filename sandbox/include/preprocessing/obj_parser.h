#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include "parser.h"
#include <assert.h>
#include "../architecture/mesh.h"

void parseObjFile(char* path, Mesh* m);

#endif