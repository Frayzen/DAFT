#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include "parser.h"
#include <assert.h>
#include "../architecture/mesh.h"
#include "../architecture/vectors.h"

void parseObjFile(char* path, Mesh* m);

#endif