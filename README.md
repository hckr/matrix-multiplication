# Matrix multiplication in C++

## How to build

```bash
cd build
# cmake -DCMAKE_BUILD_TYPE=Debug .. # openmp parallel for is faster (but all are slow in general)
cmake -DCMAKE_BUILD_TYPE=Release ..
make
cd ../dist # executables should be here
```
