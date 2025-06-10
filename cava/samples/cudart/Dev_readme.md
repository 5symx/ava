# Reproduction for  CUDA Runtime (`cudart`)

## Setup and Build

To generate and build the CUDA runtime demo:

```sh
./generate.py -s cudart
# choose ccmake demo + CUDA runtime
make -j$(nproc)
make install
```

### Compile Test Program

Use the following command to compile the test program:

```sh
gcc -o test test.c \
    -I/usr/local/cuda/include \
    -L../../../../build/install/cudart/lib -lcudart -lcuda
```

### Run Demo Manager

```sh
./install/bin/demo_manager --worker_path install/cudart/bin/worker
LD_LIBRARY_PATH=install/cudart/lib ../cava/samples/cudart/test_program/test
```

⚠ **Note:** The manager **must be run inside Docker**, otherwise it cannot find `libcudart.so.10.1`.

---

## Rodinia - CUDA Runtime Check

### **Step 1: Configure `cudart/bfs/run`**
1. **Set `LIB_PATH`**  
   - Use the original CUDA runtime path:
   ```sh
   /usr/local/cuda/lib64/
   ```
   - Verify that the correct `libcudart.so` is being used.

2. **Set `data_dir`**  
   - Configure the dataset path:
   ```sh
   ava/third_party/ava-benchmarks/rodinia/my_dataset/rodinia-data/bfs
   ```

### **Step 2: Configure `cudart/scripts/make.config`**
- Set `AVA_LIB` appropriately.

### **STEP 3: test in docker**
```sh
# docker manager
./install/bin/demo_manager --worker_path install/cudart/bin/worker
# docker worker
LD_LIBRARY_PATH=install/cudart/lib ../third_party/ava-benchmarks/rodinia/cudart/bfs/run 
```

