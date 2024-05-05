#include <mpich/mpi.h>
#include <bits/stdc++.h>


using namespace std;


void printMatrix(double **mat, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}


void AddMatrices(double **A, double **B, double **&C,
                 int A_row, int A_col) {
    for (int i = 0; i < A_row; i++) {
        for (int j = 0; j < A_col; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


void initializeMatrix(double **&A, double *&Adata, int A_row, int A_col) {
    Adata = (double *) malloc(sizeof(double) * A_row * A_col);
    A = (double **) malloc(sizeof(double *) * A_row);
    for (int i = 0; i < A_row; i++) {
        A[i] = &(Adata[i * A_col]);
    }
}

int main(int argc, char **argv) {
    int rank, size;
    int strip_size_A, A_row, A_col;
    // **A is the matrix, *Adata is a flattened 1D of it.
    double **A, *Adata, **B, *Bdata, **strip_A, *stripdataA, **strip_B, *stripdataB,
            **part, *partdata, **res, *resdata;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        cout << "This program calculates matrix Addition (A+B): " << endl;
        cout << "Enter Number of Rows for A & B: " << endl;
        cin >> A_row;
        cout << "Enter Number of Columns for A & B: " << endl;
        cin >> A_col;

        if (A_row % size != 0) {
            cerr << "Matrix can NOT be parallelized" << endl;
            exit(-1);
        }

        /* calculate the strip size of A*/
        strip_size_A = A_row / size;

        /* initialize & generate values of Matrix A & B */
        initializeMatrix(A, Adata, A_row, A_col);
        initializeMatrix(B, Bdata, A_row, A_col);
        for (int i = 0; i < A_row; i++) {
            for (int j = 0; j < A_col; j++) {
                B[i][j] = A[i][j] = i * j;
            }
        }
    }

    /* Begin Time Calculation */
    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    /* Broadcasting */
    MPI_Bcast(&A_row, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&A_col, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&strip_size_A, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /* Initialize Matrix strip_A/B, part, and res */
    initializeMatrix(strip_A, stripdataA, strip_size_A, A_col);
    initializeMatrix(strip_B, stripdataB, strip_size_A, A_col);
    initializeMatrix(part, partdata, strip_size_A, A_col);
    initializeMatrix(res, resdata, A_row, A_col);

    /* Scatter Matrix A/B to strip_A/B properly */
    MPI_Scatter(Adata, A_col * strip_size_A,
                MPI_DOUBLE, &(strip_A[0][0]),
                A_col * strip_size_A,
                MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Scatter(Bdata, A_col * strip_size_A,
                MPI_DOUBLE, &(strip_B[0][0]),
                A_col * strip_size_A,
                MPI_DOUBLE, 0, MPI_COMM_WORLD);


    /* Do the operation for the subMatrices */
    AddMatrices(strip_A, strip_B, part, strip_size_A, A_col);

    /* Gather subResults into the master node */
    MPI_Gather(&(part[0][0]), strip_size_A * A_col, MPI_DOUBLE,
               resdata, strip_size_A * A_col,
               MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* End Time */
    double end = MPI_Wtime();

    if (rank == 0) {
        cout << "Matrix A: " << endl;
        printMatrix(A, A_row, A_col);
        cout << "Matrix B: " << endl;
        printMatrix(B, A_row, A_col);
        cout << "Matrix A+B: " << endl;
        printMatrix(res, A_row, A_col);
        cout << "Time: " << (end - start) * 1000 << " ms" << endl;
    }
    MPI_Finalize();
    return 0;
}