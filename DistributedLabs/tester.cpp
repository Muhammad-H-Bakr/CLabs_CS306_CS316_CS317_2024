#include "tester.h"

void createMatrix(int **&pointer, int n, int m) {
    pointer = (int **) (malloc(sizeof(int *) * n));
    for (int i = 0; i < n; i++) {
        int *helper = (int *) (malloc(sizeof(int) * m));
        pointer[i] = helper;
    }
    random_device rd;
    mt19937 gen(rd());

    // Define a distribution for double values between 0 and 1
    uniform_real_distribution<double> dist(0.0, 10.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pointer[i][j] = (int) dist(gen);
        }
    }
}

void createMatrix2(double **&pointer, int n, int m) {
    pointer = (double **) (malloc(sizeof(double *) * n));
    for (int i = 0; i < n; i++) {
        auto *helper = (double *) (malloc(sizeof(double) * m));
        pointer[i] = helper;
    }
    // Seed the random number generator
    random_device rd;
    mt19937 gen(rd());

    // Define a distribution for double values between 0 and 1
    uniform_real_distribution<double> dist(0.0, 10.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //Fetch the random number:
            pointer[i][j] = dist(gen);
        }
    }
}

void addMatrices1(int **&C, int **&A, int **&B, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void addMatrices2(int **&C, int **&A, int **&B, int n, int m) {
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


double trapQuad(double a, double b) {
    double N = 100;
    double h = (b - a) / N;
    double I = (h / 2) * ((pow(a, 2) + pow(b, 2)));
    for (double i = a + h; i < b; i += h) { // NOLINT(*-flp30-c)
        I += h * pow(i, 2);
    }
    return I;
}

void multiplyMatrix(double **&C, double **&A, double **&B, int n, int m, int k, int q) {
/*Takes two matrices A(n*m) and B(k*q) and puts their
multiplication in C(n*q) [Given of course m = k].*/
    if (m == k) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < q; j++) {
                for (int l = 0; l < k; l++) {
                    C[i][j] = A[i][l] * B[l][j];
                }
            }
        }
    } else {
        cerr << "Invalid Matrix Multiplication." << endl;
    }
}