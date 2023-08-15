#ifndef OPENCL_H
#define OPENCL_H

/* Sources: http://www.eriksmistad.no/getting-started-with-opencl-and-gpu-computing/ */

// openCL headers
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define CL_TARGET_OPENCL_VERSION 120
#include <CL/cl.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)

typedef struct {
    cl_device_id deviceID;
    cl_context context;
    cl_command_queue commandQueue;
    cl_program program;
    cl_kernel kernel;
    cl_mem result;
} DaftOpenCL;


DaftOpenCL* initOpenCL();
void freeOpenCL(DaftOpenCL* openCL);
#include "../window/window.h"
int* raycastMesh(Camera* camera, Mesh* mesh, DaftOpenCL* openCL);

#endif