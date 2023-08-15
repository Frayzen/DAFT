#include "../../include/acceleration/opencl.h"

DaftOpenCL* initOpenCL(){
	DaftOpenCL* acceleration = (DaftOpenCL*)malloc(sizeof(DaftOpenCL));
	FILE *kernelFile;
	char *kernelSource;
	size_t kernelSize;

	kernelFile = fopen("cl/kernel.cl", "r");

	if (!kernelFile) {

		fprintf(stderr, "No file named kernel.cl was found\n");

		exit(-1);

	}
	
	kernelSource = (char*)malloc(MAX_SOURCE_SIZE);
	kernelSize = fread(kernelSource, 1, MAX_SOURCE_SIZE, kernelFile);
	fclose(kernelFile);

	// Getting platform and device information
	cl_platform_id platformId = NULL;
	cl_device_id deviceID = NULL;
	cl_uint retNumDevices;
	cl_uint retNumPlatforms;
	cl_int ret = clGetPlatformIDs(1, &platformId, &retNumPlatforms);
	ret = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_DEFAULT, 1, &deviceID, &retNumDevices);

	// Creating context.
	cl_context context = clCreateContext(NULL, 1, &deviceID, NULL, NULL,  &ret);

	// Creating command queue
	cl_command_queue commandQueue = clCreateCommandQueue(context, deviceID, 0, &ret);

	acceleration->deviceID = deviceID;
	acceleration->context = context;
	acceleration->commandQueue = commandQueue;

	// Create program from kernel source
	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&kernelSource, (const size_t *)&kernelSize, &ret);	

	// Build program
	ret = clBuildProgram(program, 1, &deviceID, NULL, NULL, NULL);

	// Create kernel
	cl_kernel kernel = clCreateKernel(program, "raytrace", &ret);

	// Create memory buffers on the device for each vector
	cl_mem rayBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(Vector3) * SCREEN_HEIGHT * SCREEN_WIDTH, NULL, &ret);
	acceleration->result = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * SCREEN_HEIGHT * SCREEN_WIDTH, NULL, &ret);


	// Set arguments for kernel
	ret = clSetKernelArg(kernel, 5, sizeof(cl_mem), (void *)&acceleration->result);
	assert(ret == CL_SUCCESS);

	return acceleration;
}

void freeOpenCL(DaftOpenCL* openCL){
	int ret;
	ret = clReleaseCommandQueue(openCL->commandQueue);
	assert(ret == CL_SUCCESS);
	ret = clReleaseKernel(openCL->kernel);
	assert(ret == CL_SUCCESS);
	ret = clReleaseProgram(openCL->program);
	assert(ret == CL_SUCCESS);
	ret = clReleaseMemObject(openCL->result);
	assert(ret == CL_SUCCESS);
	ret = clReleaseContext(openCL->context);
	assert(ret == CL_SUCCESS);
}

int* raycastMesh(Camera* camera, Mesh* mesh, DaftOpenCL* openCL){
	int ret;
	cl_kernel kernel = openCL->kernel; 
	cl_command_queue commandQueue = openCL->commandQueue;
	cl_context context = openCL->context;
	cl_mem result = openCL->result;

	// Memory buffers for each array
	cl_mem verticesBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Vector3) * mesh->vertexCount, NULL, &ret);
	cl_mem trianglesBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Triangle) * mesh->triangleCount, NULL, &ret);
	cl_mem rayBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Vector3) * SCREEN_HEIGHT * SCREEN_WIDTH, NULL, &ret);

	// Copy lists to memory buffers
	ret = clEnqueueWriteBuffer(openCL->commandQueue, verticesBuffer, CL_TRUE, 0, sizeof(Vector3) * mesh->vertexCount, mesh->vertices, 0, NULL, NULL);
	assert(ret == CL_SUCCESS);
	ret = clEnqueueWriteBuffer(openCL->commandQueue, trianglesBuffer, CL_TRUE, 0, sizeof(Triangle) * mesh->triangleCount, mesh->triangles, 0, NULL, NULL);
	assert(ret == CL_SUCCESS);
	ret = clEnqueueWriteBuffer(openCL->commandQueue, rayBuffer, CL_TRUE, 0, sizeof(Vector3) * SCREEN_HEIGHT * SCREEN_WIDTH, camera->rays, 0, NULL, NULL);


	// Set arguments for kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_float3), &camera->rotation);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&rayBuffer);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&verticesBuffer);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&trianglesBuffer);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 4, sizeof(int), &mesh->triangleCount);
	assert(ret == CL_SUCCESS);

	// Execute the kernel
	size_t globalItemSize[2] = {SCREEN_HEIGHT, SCREEN_WIDTH};
	size_t localItemSize = 1;
	ret = clEnqueueNDRangeKernel(openCL->commandQueue, kernel, 2, NULL, globalItemSize, &localItemSize, 0, NULL, NULL);

	// Read from device back to host.
	int* resultArray = (int*)malloc(sizeof(int) * SCREEN_HEIGHT * SCREEN_WIDTH);
	ret = clEnqueueReadBuffer(openCL->commandQueue, openCL->result, CL_TRUE, 0, sizeof(int) * SCREEN_HEIGHT * SCREEN_WIDTH, result, 0, NULL, NULL);

	// Clean up, release memory.
	ret = clFlush(openCL->commandQueue);
	ret = clFinish(commandQueue);
	return resultArray;
}
