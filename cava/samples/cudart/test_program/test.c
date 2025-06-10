#include <cuda.h>
#include <stdio.h>

int main() {
    CUdevice device;
    CUcontext context;
    int deviceCount = 0;
    char deviceName[256];

    // Initialize the CUDA Driver API
    // Initialize the CUDA Driver API
    cuInit(0);

    // Get the number of CUDA devices
    cuDeviceGetCount(&deviceCount);
    printf("Number of CUDA devices: %d\n", deviceCount);

}
