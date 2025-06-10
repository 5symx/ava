# CUDADRV

## Running CUDADRV (Same as Demo)
The process for **CUDADRV** is similar to the demo setup.

GitHub Repository:  
[AVA Worker Demo](https://github.com/utcs-scea/ava/tree/c40e33fada3520990552f99af6113f4671aaaa06/worker/demo)

### Creating a Test Program
To create and run a **test program** for CUDADRV:
```sh
./install/bin/demo_manager --worker_path install/cudadrv/bin/worker
LD_LIBRARY_PATH=install/cudadrv/lib ../cava/samples/cudadrv/test_program/test

```

## Ronidia Benchmark(ERROR)
> ⚠ **TBC:**  driver version 12090 vs toolkit inside docker 10.1

Using ava-benchmark for CUDA driver api test:
1. update nvidia.mk file for env path
2. update bfs_cuda.c change cubin to ptx for compatibility
```sh

./install/bin/demo_manager --worker_path install/cudadrv/bin/worker

LD_LIBRARY_PATH=install/cudadrv/lib ../third_party/ava-benchmarks/rodinia/cuda/bfs/bfs ../third_party/ava-benchmarks/rodinia/cuda/bfs/graph65536.txt

```
### debugging
cuModuleLoad() failed:
1. output error code 218(CUDA_ERROR_INVALID_PTX)
2. ptx compile with cuda 10.1 but running driver version is 12090 (cuDriverGetVersion)
3. ptx file cannot be load from manager, but can load locally in cuda10.1 at /usr/local/cuda.

