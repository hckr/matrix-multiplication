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

### Parallel forst loop

matrix size | sequential | 2 | 4 | 8 | 16
------------|------------|---|---|---|----
100x100     | 0.014921 s | 0.017341 s | 0.029749 s | 0.016134 s | 0.02311 s
500x500     | 0.144012 s | 0.166371 s | 0.192614 s | 0.188561 s | 0.187832 s
1000x1000   | 0.544923 s | 0.611869 s | 0.623932 s | 0.607837 s | 0.637272 s
2000x2000   | 2.31109 s  | 2.38459 s  | 2.42206 s  | 2.38902 s  | 2.38259 s


### Parallel second loop

matrix size | sequential | 2 | 4 | 8 | 16
------------|------------|---|---|---|----
100x100     | 0.014921 s | 0.017985 s | 0.02853 s  | 0.019828 s | 0.021241 s
500x500     | 0.144012 s | 0.179789 s | 0.197931 s | 0.168557 s | 0.169127 s
1000x1000   | 0.544923 s | 0.610792 s | 0.626924 s | 0.60476 s | 0.613628 s
2000x2000   | 2.31109 s  | 2.40542 s  | 2.42915 s  | 2.42213 s  | 2.45789 s
