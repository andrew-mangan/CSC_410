// Matrix Multiplicaton using OpenCL

#define CL_TARGET_OPENCL_VERSION 120
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>

const char *kernelSource = R"(
__kernel void matrixMultiply(__global float* A, 
                             __global float* B, 
                             __global float* C, 
                             const int N) {
    int row = get_global_id(0);
    int col = get_global_id(1);
    
    float sum = 0.0;
    for (int k = 0; k < N; k++) {
        sum += A[row * N + k] * B[k * N + col];
    }
    C[row * N + col] = sum;
}
)";


int main() {
 
    
    const int N = 100000; // Matrix dimension
    size_t bytes = N * N * sizeof(float);

    // Host data
    float *A = (float*)malloc(bytes);
    float *B = (float*)malloc(bytes);
    float *C = (float*)malloc(bytes);

    // Initialize matrices
    for (int i = 0; i < N * N; i++) {
        A[i] = 1.0f; 
        B[i] = 1.0f; 
        C[i] = 0.0f;
    }

    // OpenCL setup and matrix multiplication
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue command_queue;
    cl_int ret;
    cl_program program;
    cl_kernel kernel;

// Get the first platform/device/context/command queue
    ret = clGetPlatformIDs(1, &platform, NULL);
    if(ret != CL_SUCCESS){
        printf("Failed to find OpenCL platform.\n");
        return -1;
    }
    ret = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (ret != CL_SUCCESS){
        printf("Fail again to do anything good.\n");
        return -1;
    }
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &ret);
    if (ret != CL_SUCCESS){
        printf("againt failed to create context.\n");
        return -1;
    }
    command_queue = clCreateCommandQueue(context, device, 0, &ret);
    if (ret != CL_SUCCESS){
        printf("Failed to create command queue.\n");
        return -1;
    }
    
    printf("OpenCL Platform and Device initialized successfully.\n");

    // Allocate memory on device
    cl_mem bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, &ret);
    cl_mem bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, &ret);
    cl_mem bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bytes, NULL, &ret);
    
    // Copy Matrices A/B to device
    clEnqueueWriteBuffer(command_queue, bufferA, CL_TRUE, 0, sizeof(float) * N * N, A, 0, NULL, NULL);
    clEnqueueWriteBuffer(command_queue, bufferB, CL_TRUE, 0, sizeof(float) * N * N, B, 0, NULL, NULL);
    //create kernal 
    program = clCreateProgramWithSource(context, 1, &kernelSource, NULL, &ret);
    clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    kernel = clCreateKernel(program, "matrixMultiply", &ret);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&bufferA);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&bufferB);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&bufferC);
    clSetKernelArg(kernel, 3, sizeof(const int), (void*) &N);
    clEnqueueTask(command_queue, kernel, 0, NULL, NULL);

    // Define the global and local work sizes
    size_t globalSize[2] = {N, N};
    size_t localSize[2] = {100, 100};  

    // Execute the kernel
    clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, globalSize, localSize, 0, NULL, NULL);

    // Read the result back to host
    clEnqueueReadBuffer(command_queue, bufferC, CL_TRUE, 0, sizeof(float) * N * N, C, 0, NULL, NULL);

    // Wait for the command queue to finish
    clFinish(command_queue);


    /* Print result
     printf("Result Matrix:\n");
     for (int i = 0; i < N; i++) {
         for (int j = 0; j < N; j++) {
             printf("%f ", C[i * N + j]);
         }
        printf("\n");
     }*/

     //Cleanup

    printf("program has completed.\n");
    clReleaseMemObject(bufferA);
    clReleaseMemObject(bufferB);
    clReleaseMemObject(bufferC);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(command_queue);
    clReleaseContext(context);

    free(A);
    free(B);
    free(C);


    return 0;
}