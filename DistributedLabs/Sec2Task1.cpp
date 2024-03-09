#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"

#include "tester.h"

int main() {
    int n, m;
    n = m = 1000;
    int **A, **B, **C;
    createMatrix(A, n, m);
    createMatrix(B, n, m);
    createMatrix(C, n, m);
    auto start = high_resolution_clock::now();
    addMatrices1(C, A, B, n, m);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Time for the first algorithm: " << duration.count() << "ns" << endl;
    start = high_resolution_clock::now();
    addMatrices2(C, A, B, n, m);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "Time for the second algorithm: " << duration.count() << "ns" << endl;
    return 0;
}

#pragma clang diagnostic pop