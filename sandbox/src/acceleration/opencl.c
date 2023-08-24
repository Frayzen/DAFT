#include "../../include/acceleration/opencl.h"

DaftOpenCL* initOpenCL(){
	DaftOpenCL* openCL = (DaftOpenCL*)malloc(sizeof(DaftOpenCL));
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
	cl_uint retNumDevices;
	cl_uint retNumPlatforms;
	cl_int ret = clGetPlatformIDs(1, &platformId, &retNumPlatforms);
	ret = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_DEFAULT, 1, &openCL->deviceID, &retNumDevices);

	// Creating context.
	openCL->context = clCreateContext(NULL, 1, &openCL->deviceID, NULL, NULL,  &ret);

	// Creating command queue
	cl_command_queue commandQueue = clCreateCommandQueue(openCL->context, openCL->deviceID, 0, &ret);

	openCL->commandQueue = commandQueue;

	// Create program from kernel source
	openCL->program = clCreateProgramWithSource(openCL->context, 1, (const char **)&kernelSource, (const size_t *)&kernelSize, &ret);	

	// Build program
	ret = clBuildProgram(openCL->program, 1, &openCL->deviceID, NULL, NULL, NULL);
	if(ret != CL_SUCCESS){
		size_t len;
		char buffer[2048];
		clGetProgramBuildInfo(openCL->program, openCL->deviceID, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%s\n", buffer);
		exit(-1);
	}

	// Create kernel
	openCL->kernel = clCreateKernel(openCL->program, "raytrace", &ret);
	assert(ret == CL_SUCCESS);

	// Create memory buffers on the device for each vector
	cl_mem rayBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Vector3) * SCREEN_HEIGHT * SCREEN_WIDTH, NULL, &ret);
	openCL->result = clCreateBuffer(openCL->context, CL_MEM_WRITE_ONLY, sizeof(unsigned int) * SCREEN_HEIGHT * SCREEN_WIDTH, NULL, &ret);

	// Set arguments for kernel
	ret = clSetKernelArg(openCL->kernel, 10, sizeof(cl_mem), (void *)&openCL->result);
	assert(ret == CL_SUCCESS);

	return openCL;
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

void raycastMesh(Camera* camera, Mesh* mesh, DaftOpenCL* openCL, unsigned int* resultArray){
	int ret;
	cl_kernel kernel = openCL->kernel; 
	cl_command_queue commandQueue = openCL->commandQueue;
	cl_context context = openCL->context;

	int normalCount = max(1, mesh->normalCount);

	// Memory buffers for each array
	cl_mem verticesBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Vector3) * mesh->vertexCount, NULL, &ret);
	cl_mem normalsBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Vector3) * normalCount, NULL, &ret);
	cl_mem trianglesBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Triangle) * mesh->triangleCount, NULL, &ret);
	cl_mem rayBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Vector3) * SCREEN_HEIGHT * SCREEN_WIDTH, NULL, &ret);
	cl_mem rotationBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Matrix3), NULL, &ret);
	cl_mem positionBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Vector3), NULL, &ret);
	cl_mem minbboxBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Vector3) * mesh->bboxCount, NULL, &ret);
	cl_mem maxbboxBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(Vector3) * mesh->bboxCount, NULL, &ret);
	cl_mem childrenbboxBuffer = clCreateBuffer(openCL->context, CL_MEM_READ_ONLY, sizeof(int2) * mesh->bboxCount, NULL, &ret);

	// Copy lists to memory buffers
	ret = clEnqueueWriteBuffer(openCL->commandQueue, verticesBuffer, CL_TRUE, 0, sizeof(Vector3) * mesh->vertexCount, mesh->vertices, 0, NULL, NULL);
	assert(ret == CL_SUCCESS);
	ret = clEnqueueWriteBuffer(openCL->commandQueue, normalsBuffer, CL_TRUE, 0, sizeof(Vector3) * normalCount, mesh->normals, 0, NULL, NULL);
	assert(ret == CL_SUCCESS);
	ret = clEnqueueWriteBuffer(openCL->commandQueue, trianglesBuffer, CL_TRUE, 0, sizeof(Triangle) * mesh->triangleCount, mesh->triangles, 0, NULL, NULL);
	assert(ret == CL_SUCCESS);
	ret = clEnqueueWriteBuffer(openCL->commandQueue, rayBuffer, CL_TRUE, 0, sizeof(Vector3) * SCREEN_HEIGHT * SCREEN_WIDTH, camera->rays, 0, NULL, NULL);
	assert(ret == CL_SUCCESS);
	ret = clEnqueueWriteBuffer(openCL->commandQueue, openCL->result, CL_TRUE, 0, sizeof(int) * SCREEN_HEIGHT * SCREEN_WIDTH, resultArray, 0, NULL, NULL);
	assert(ret == CL_SUCCESS);
	Matrix3 rotationMatrix = createRotationMatrix(camera->rotation);
	ret = clEnqueueWriteBuffer(openCL->commandQueue, rotationBuffer, CL_TRUE, 0, sizeof(Matrix3), &rotationMatrix, 0, NULL, NULL);
	assert(ret == CL_SUCCESS);
	ret = clEnqueueWriteBuffer(openCL->commandQueue, positionBuffer, CL_TRUE, 0, sizeof(Vector3), &(camera->position), 0, NULL, NULL);
	assert(ret == CL_SUCCESS);
	ret = clEnqueueWriteBuffer(openCL->commandQueue, minbboxBuffer, CL_TRUE, 0, sizeof(Vector3) * mesh->bboxCount, mesh->minBbox, 0, NULL, NULL);
	assert(ret == CL_SUCCESS);
	ret = clEnqueueWriteBuffer(openCL->commandQueue, maxbboxBuffer, CL_TRUE, 0, sizeof(Vector3) * mesh->bboxCount, mesh->maxBbox, 0, NULL, NULL);
	assert(ret == CL_SUCCESS);
	ret = clEnqueueWriteBuffer(openCL->commandQueue, childrenbboxBuffer, CL_TRUE, 0, sizeof(int2) * mesh->bboxCount, mesh->children, 0, NULL, NULL);
	assert(ret == CL_SUCCESS);

	// Set arguments for kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&positionBuffer);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&rotationBuffer);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&rayBuffer);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&verticesBuffer);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&normalsBuffer);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 5, sizeof(cl_mem), (void *)&trianglesBuffer);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 6, sizeof(cl_int), &mesh->triangleCount);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 7, sizeof(cl_mem), (void *)&minbboxBuffer);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 8, sizeof(cl_mem), (void *)&maxbboxBuffer);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 9, sizeof(cl_mem), (void *)&childrenbboxBuffer);
	assert(ret == CL_SUCCESS);

	// Execute the kernel
	size_t globalItemSize[2] = {SCREEN_HEIGHT, SCREEN_WIDTH};
	size_t localItemSize = 1;
	ret = clEnqueueNDRangeKernel(openCL->commandQueue, kernel, 2, NULL, globalItemSize, &localItemSize, 0, NULL, NULL);

	// Read from device back to host.
	ret = clEnqueueReadBuffer(openCL->commandQueue, openCL->result, CL_TRUE, 0, sizeof(int) * SCREEN_HEIGHT * SCREEN_WIDTH, resultArray, 0, NULL, NULL);
	ret = clFlush(openCL->commandQueue);

	// Free memory buffers
	ret = clReleaseMemObject(verticesBuffer);
	assert(ret == CL_SUCCESS);
	ret = clReleaseMemObject(normalsBuffer);
	assert(ret == CL_SUCCESS);
	ret = clReleaseMemObject(trianglesBuffer);
	assert(ret == CL_SUCCESS);
	ret = clReleaseMemObject(rayBuffer);
	assert(ret == CL_SUCCESS);
	ret = clReleaseMemObject(rotationBuffer);
	assert(ret == CL_SUCCESS);
	ret = clReleaseMemObject(positionBuffer);
	assert(ret == CL_SUCCESS);
	ret = clReleaseMemObject(minbboxBuffer);
	assert(ret == CL_SUCCESS);
	ret = clReleaseMemObject(maxbboxBuffer);
	assert(ret == CL_SUCCESS);
	ret = clReleaseMemObject(childrenbboxBuffer);
	assert(ret == CL_SUCCESS);
}


void finishRaycasting(DaftOpenCL* openCL){
	int ret;
	ret = clFinish(openCL->commandQueue);
	assert(ret == CL_SUCCESS);
}