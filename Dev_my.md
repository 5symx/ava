
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

