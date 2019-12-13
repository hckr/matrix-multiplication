# Time tests report

`cmake -DCMAKE_BUILD_TYPE=Release .. && make`

[multiply.cpp#L11](matrix_multiplication/parallel/multiply.cpp#L11)
```cpp
for (unsigned r = 0; r < result.numRows(); ++r) { // first loop
    for (unsigned c = 0; c < result.numCols(); ++c) { // second loop
        double sum = 0;
        for (unsigned i = 0; i < m1.numRows(); ++i) {
            sum = sum + m1a[r * m1.numCols() + i] * m2a[i * m2.numCols() + c];
        }
        ra[r * result.numCols() + c] = sum;
    }
}
```

## Intel Core i5-4210U CPU @ 1.70GHz, 7.7 GiB RAM

### Parallel first loop

matrix size | sequential | 2 | 4 | 8 | 16
------------|------------|---|---|---|----
100x100     | 0.00104149 s | 0.000743524 s | 0.00276629 s | 0.00109699 s | 0.0006394 s
500x500     | 0.1771 s | 0.0990671 s | 0.0948462 s | 0.0930083 s | 0.134058 s
1000x1000   | 3.34358 s | 1.5445 s | 5.21199 s | 5.43917 s | 5.4042 s
2000x2000   | 97.5696 s | 52.4541 s | 59.4125 s | 60.8381 s | 61.18 s


### Parallel second loop

matrix size | sequential | 2 | 4 | 8 | 16
------------|------------|---|---|---|----
100x100     | 0.00104149 s | 0.000774378 s | 0.000892897 s | 0.008705 s | 0.0110233 s
500x500     | 0.1771 s | 0.105213 s | 0.0978214 s | 0.119072 s | 0.156579 s
1000x1000   | 3.34358 s | 2.25636 s | 5.53892 s | 5.44094 s | 5.54246 s
2000x2000   | 97.5696 s | 54.5628 s | 62.612 s | 63.5937 s | 61.0127 s
