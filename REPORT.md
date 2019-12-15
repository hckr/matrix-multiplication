# Zrównoleglanie mnożenia macierzy

Zadaniem było wykonanie programu/ów w języku C/C++ obliczających iloczyn macierzy metodą sekwencyjną oraz zrównoleglenie go na różne sposoby wymienione poniżej za pomocą biblioteki OpenMP.

## Fragmenty kodu

### Wczytywanie macierzy z plików:

```C++
Matrix loadMatrix(std::string file_name) {
    // ...
    std::ifstream stream(file_name);
    return Matrix(stream);
}

// ...

std::unique_ptr<Matrix> first;
std::unique_ptr<Matrix> second;

#pragma omp parallel sections
{
    #pragma omp section
    {
        first.reset(new Matrix(loadMatrix(argv[1])));
    }
    #pragma omp section
    {
        second.reset(new Matrix(loadMatrix(argv[2])));
    }
}
```

### Mnożenie macierzy:

```C++
for (unsigned r = 0; r < result.numRows(); ++r) {
    for (unsigned c = 0; c < result.numCols(); ++c) {
        double sum = 0;
        for (unsigned i = 0; i < m1.numRows(); ++i) {
            sum = sum + m1a[r * m1.numCols() + i] * m2a[i * m2.numCols() + c];
        }
        ra[r * result.numCols() + c] = sum;
    }
}
```

### Zrównoleglenie pierwszej pętli:

```C++
#pragma omp parallel for
    for (unsigned r = 0; r < result.numRows(); ++r) {
        for (unsigned c = 0; c < result.numCols(); ++c) {
            double sum = 0;
            for (unsigned i = 0; i < m1.numRows(); ++i) {
                sum = sum + m1a[r * m1.numCols() + i] * m2a[i * m2.numCols() + c];
            }
            ra[r * result.numCols() + c] = sum;
        }
    }
}
```

### Zrównoleglenie drugiej pętli:

```C++
for (unsigned r = 0; r < result.numRows(); ++r) {
    #pragma omp parallel for
    for (unsigned c = 0; c < result.numCols(); ++c) {
        double sum = 0;
        for (unsigned i = 0; i < m1.numRows(); ++i) {
            sum = sum + m1a[r * m1.numCols() + i] * m2a[i * m2.numCols() + c];
        }
        ra[r * result.numCols() + c] = sum;
    }
}

```

### Zrównoleglenie trzeciej pętli:

**To zrównoleglenie jest niepoprawne**, gdyż każda iteracja pętli odczytuje i nadpisuje zmienną `sum`, co prowadzi do sytuacji niedeterministycznych, a już z pewnością niepoprawnych, wyników.

```C++
for (unsigned r = 0; r < result.numRows(); ++r) {
    for (unsigned c = 0; c < result.numCols(); ++c) {
        double sum = 0;
        #pragma omp parallel for
        for (unsigned i = 0; i < m1.numRows(); ++i) {
            sum = sum + m1a[r * m1.numCols() + i] * m2a[i * m2.numCols() + c];
        }
        ra[r * result.numCols() + c] = sum;
    }
}

```

## Wyniki pomiarów czasu wykonania programu dla poprawnych zrównolegleń

Pomiarów dokonałem na dwóch maszynach.

## Intel Core i5-4210U CPU @ 1.70GHz, 7.7 GiB RAM

### Zrównoleglenie pierwszej pętli

wielkość macierzy | sekwencyjnie | 2 wątki | 4 wątki | 8 wątków | 16 wątków
------------|------------|---|---|---|----
100x100     | 0.00104149 s | 0.000743524 s | 0.00276629 s | 0.00109699 s | 0.0006394 s
500x500     | 0.1771 s | 0.0990671 s | 0.0948462 s | 0.0930083 s | 0.134058 s
1000x1000   | 3.34358 s | 1.5445 s | 5.21199 s | 5.43917 s | 5.4042 s
2000x2000   | 97.5696 s | 52.4541 s | 59.4125 s | 60.8381 s | 61.18 s


### Zrównoleglenie drugiej pętli

wielkość macierzy | sekwencyjnie | 2 wątki | 4 wątki | 8 wątków | 16 wątków
------------|------------|---|---|---|----
100x100     | 0.00104149 s | 0.000774378 s | 0.000892897 s | 0.008705 s | 0.0110233 s
500x500     | 0.1771 s | 0.105213 s | 0.0978214 s | 0.119072 s | 0.156579 s
1000x1000   | 3.34358 s | 2.25636 s | 5.53892 s | 5.44094 s | 5.54246 s
2000x2000   | 97.5696 s | 54.5628 s | 62.612 s | 63.5937 s | 61.0127 s

### Zrównoleglenie pierwszej pętli z różnymi wartościami schedule

liczba wątków | schedule, chunk size | 1000x1000 | 2000x2000
----|-------------|-----------|-----------
2   | static, 10  | 4.34592 s | 51.7398 s
4   | static, 10  | 4.72894 s | 60.6341 s
8   | static, 10  | 4.48876 s | 62.5849 s
16  | static, 10  | 3.42955 s | 61.306 s
2   | static, 50  | 1.83207 s | 79.0045 s
4   | static, 50  | 4.86706 s | 62.2272 s
8   | static, 50  | 4.50592 s | 61.9995 s
16  | static, 50  | 4.66699 s | 61.3982 s
2   | static, 100 | 1.85873 s | 55.679 s
4   | static, 100 | 4.62542 s | 61.4036 s
8   | static, 100 | 4.38563 s | 59.6304 s
16  | static, 100 | 4.40969 s | 62.1475 s
2   | dynamic, 10  | 1.72321 s | 53.5435 s
4   | dynamic, 10  | 4.86353 s | 60.7721 s
8   | dynamic, 10  | 5.05537 s | 61.004 s
16  | dynamic, 10  | 5.10825 s | 61.6963 s
2   | dynamic, 50  | 1.60674 s | 54.8837 s
4   | dynamic, 50  | 4.8612 s | 61.5971 s
8   | dynamic, 50  | 4.82382 s | 62.0046 s
16  | dynamic, 50  | 5.07994 s | 63.7101 s
2   | dynamic, 100 | 1.62911 s | 54.7317 s
4   | dynamic, 100 | 4.93039 s | 61.8916 s
8   | dynamic, 100 | 5.20774 s | 62.2251 s
16  | dynamic, 100 | 5.10253 s | 61.263 s
2   | guided, 10  | 1.566 s | 55.6141 s
4   | guided, 10  | 4.88217 s | 62.2654 s
8   | guided, 10  | 5.05663 s | 61.9371 s
16  | guided, 10  | 5.0244 s | 63.5362 s
2   | guided, 50  | 1.55273 s | 61.1701 s
4   | guided, 50  | 4.98968 s | 62.8993 s
8   | guided, 50  | 4.99365 s | 62.5224 s
16  | guided, 50  | 5.09124 s | 59.3034 s
2   | guided, 100 | 1.67578 s | 58.2409 s
4   | guided, 100 | 4.53516 s | 58.9875 s
8   | guided, 100 | 5.03139 s | 59.8628 s
16  | guided, 100 | 4.95006 s | 61.3655 s


## Intel Core i7-7700HQ CPU @ 2.80GHz, 15.4 GiB

### Zrównoleglenie pierwszej pętli

wielkość macierzy | sekwencyjnie | 2 wątki | 4 wątki | 8 wątków | 16 wątków
------------|------------|---|---|---|----
100x100     | 0.0144686 s | 0.00720714 s | 0.00311861 s | 0.0019952 s | 0.00324332 s
500x500     | 2.28354 s | 0.890355 s | 0.60179 s | 0.44751 s | 0.436572 s
1000x1000   | 18.0561 s | 7.38508 s | 4.20909 s | 4.11837 s | 4.04243 s
2000x2000   | 172.163 s | 81.7326 s | 49.8915 s | 36.0472 s | 43.2197 s


### Zrównoleglenie drugiej pętli

wielkość macierzy | sekwencyjnie | 2 wątki | 4 wątki | 8 wątków | 16 wątków
------------|------------|---|---|---|----
100x100     | 0.0144686 s | 0.00674851 s | 0.00432474 s | 0.00395922 s | 0.0269438 s
500x500     | 2.28354 s | 1.04088 s | 0.867642 s | 0.813752 s | 0.864329 s
1000x1000   | 18.0561 s | 9.7803 s | 5.26166 s | 6.23603 s | 5.67504 s
2000x2000   | 172.163 s | 104.469 s | 68.0361 s | 84.178 s | 65.289 s


### Zrównoleglenie pierwszej pętli z różnymi wartościami schedule

liczba wątków | schedule, chunk size | 1000x1000 | 2000x2000
----|-------------|-----------|-----------
2   | static, 10  | 8.57862 s | 105.739 s
4   | static, 10  | 5.25745 s | 64.8956 s
8   | static, 10  | 5.16873 s | 63.0552 s
16  | static, 10  | 5.11404 s | 63.1123 s
2   | static, 50  | 9.57832 s | 128.605 s
4   | static, 50  | 5.3367 s | 72.071 s
8   | static, 50  | 5.08325 s | 76.2903 s
16  | static, 50  | 5.30829 s | 66.9038 s
2   | static, 100 | 10.1532 s | 127.453 s
4   | static, 100 | 5.83746 s | 68.6848 s
8   | static, 100 | 5.60802 s | 59.6562 s
16  | static, 100 | 5.45384 s | 50.7019 s
2   | dynamic, 10  | 9.92337 s | 74.853 s
4   | dynamic, 10  | 5.85089 s | 44.7118 s
8   | dynamic, 10  | 5.73853 s | 38.7877 s
16  | dynamic, 10  | 5.59313 s | 46.9367 s
2   | dynamic, 50  | 9.81774 s | 99.9126
4   | dynamic, 50  | 5.83425 s | 45.0242 s
8   | dynamic, 50  | 5.74712 s | 41.378 s
16  | dynamic, 50  | 5.62734 s | 39.1366 s
2   | dynamic, 100 | 10.081 s | 75.7724 s
4   | dynamic, 100 | 6.20111 s | 46.8872 s
8   | dynamic, 100 | 5.81687 s | 46.1585 s
16  | dynamic, 100 | 5.95292 s | 34.4221 s
2   | guided, 10  | 10.3667 s | 80.5031 s
4   | guided, 10  | 6.28686 s | 46.7837 s
8   | guided, 10  | 6.17302 s | 42.748 s
16  | guided, 10  | 6.01124 s | 40.9382 s
2   | guided, 50  | 11.22 s | 75.8183 s
4   | guided, 50  | 6.00945 s | 48.6843 s
8   | guided, 50  | 6.12666 s | 43.2154 s
16  | guided, 50  | 5.8951 s | 57.2425 s
2   | guided, 100 | 10.2349 s | 90.9195 s
4   | guided, 100 | 6.12312 s | 45.1851 s
8   | guided, 100 | 6.0957 s | 37.1039 s
16  | guided, 100 | 6.05044 s | 39.1632 s


## Wnioski

W wynikach czasów wykonania programów na obu maszynach widać (w drugim wypadku wyraźniej) różnicę na korzyść zrównoleglania pierwszej, zewnętrznej pętli. Wyniki w ogóle różnią się dość pomiędzy poszczególnymi uruchomieniami testów. Uruchomienie programu na większej liczbie wątków niż liczba dostępnych procesorów daje odwrotny od zamierzonego skutek w postaci dłuższego wykonania programu niż jego wersja sekwencyjna (w wypadku pierwszej maszyny są to 2 sprzętowe wątki; mimo że procesor oferuje tzw. _hyper threading_, nie zauważono pozytywnych efektów).

Jeśli chodzi o wartości modyfikatora `schedule`, największe znaczenie wciąż ma liczba wątków, jak opisano powyżej, porównując jednak jedynie zmiany schedule wśród wyników dla optymalnej liczby wątków, najlepsze wyniki zdają się dawać, dla mniejszej macierzy `guided,10`, `guided,50` , a dla większej `dynamic,10`, `dynamic,100` (choć osobiście nie widzę żadnych wyraźnych zależności).
