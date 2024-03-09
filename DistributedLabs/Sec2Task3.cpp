#include "tester.h"

int main() {
    int n, m, k, q;
    n = m = k = q = 1000;
    double **A, **B, **C;
    createMatrix2(A, n, m);
    createMatrix2(B, k, q);
    createMatrix2(C, n, q);
    auto start = high_resolution_clock::now();
    multiplyMatrix(C, A, B, n, m, k, q);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Time for Multiplication algorithm: " << duration.count() << "ns" << endl;
    return 0;
}