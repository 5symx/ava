
# Updating Docker Image for CUDA Support

## Prerequisites
- **Update Docker image** because `nvidia/cuda` is no longer supported.
- **Ubuntu 18.04 apt repositories** no longer support CUDA, so remove the apt update repo.

## Launching Docker
To start a **Docker container** for `Ubuntu 18.04 + CUDA 10.1`, run:
```sh
./tools/docker/run_docker.sh ava-cuda-10.1
```

## Demo

### Inside Docker
Follow the documentation to **build the demo**.

### Troubleshooting

#### Issue 1: Undefined Function in `make samples/demo/test_program`
If you encounter:
```
function undefined
```
Check the linked `.so` file using:
```sh
nm -D build/install/demo/lib/libdemo.so | grep ava_test_api
```

#### Cause: C++ `.so` File Not Compatible with C Compiler
The issue occurs because the `.so` file was compiled using **C++**, but the C compiler does not accept **name-mangled symbols**.

### Solution: Modify `demo.h`
Change `demo.h` to ensure **C compatibility**:
```c
#ifdef __cplusplus
extern "C" {
#endif

void ava_test_api(int);

#ifdef __cplusplus
}
#endif
```

This prevents **C++ name mangling**, allowing the function to be correctly linked in a **C environment**.


### Running Demo Outside Docker

#### Running the Demo
To run the demo **outside the Docker container**, use:
```sh
./install/bin/demo_manager --worker_path install/demo/bin/worker

LD_LIBRARY_PATH=install/demo/lib ../cava/samples/demo/test_program/test
```

### TODO: Update Protobuf in Dockerfile
Currently, **Protobuf** needs to be updated inside the Dockerfile.

#### Temporary Fix
If Protobuf is missing, install it manually:
```sh
apt-get install -y libprotobuf-dev protobuf-compiler
ln -s /usr/lib/x86_64-linux-gnu/libprotobuf.so /usr/lib/libprotobuf.so
ldconfig
ls /usr/lib | grep protobuf
```
---

## CUDADRV

### Running CUDADRV (Same as Demo)
The process for **CUDADRV** is similar to the demo setup.

GitHub Repository:  
[AVA Worker Demo](https://github.com/utcs-scea/ava/tree/c40e33fada3520990552f99af6113f4671aaaa06/worker/demo)

### Creating a Test Program
To create and run a **test program** for CUDADRV:
```sh
./install/bin/demo_manager --worker_path install/cudadrv/bin/worker
LD_LIBRARY_PATH=install/cudadrv/lib ../cava/samples/cudadrv/test_program/test

```
### Ronidia Benchmark
Using ava-benchmark for CUDA driver api test:
1. update nvidia.mk file for env path
2. update bfs_cuda.c change cubin to ptx for compatibility
```sh

./install/bin/demo_manager --worker_path install/cudadrv/bin/worker

LD_LIBRARY_PATH=install/cudadrv/lib ../third_party/ava-benchmarks/rodinia/cuda/bfs/bfs ../third_party/ava-benchmarks/rodinia/cuda/bfs/graph65536.txt

```

#### debugging
cuModuleLoad() failed
