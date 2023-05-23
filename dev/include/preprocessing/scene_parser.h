#ifndef SCENE_PARSER_H
#define SCENE_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include "../constants.h"
#include "../architecture/world.h"
#include "../architecture/material.h"
#include "../window/window.h"
#include "../window/skybox.h"
#include "../architecture/camera.h"
#include "../architecture/ray.h"
#include "../architecture/sphere.h"
#include "../preprocessing/obj_parser.h"
world* load_scene(char* filename);

#endif