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


void MultiplyMatrices(double **A, double **B, double **&C,
                      int A_row, int A_col, int B_col) {
    for (int k = 0; k < B_col; k++) {
        for (int i = 0; i < A_row; i++) {
            C[i][k] = 0;
            for (int j = 0; j < A_col; j++) {
                C[i][k] += A[i][j] * B[j][k];
            }
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

void broadcastMatrix(double ***array, int rows, int cols, int rank) {
    if (rank == 0) {
        // Flatten the 2D array into a 1D array
        auto *buffer = (double *) malloc(rows * cols * sizeof(double));
        double *p = buffer;
        for (int i = 0; i < rows; ++i) {
            memcpy(p, (*array)[i], cols * sizeof(double));
            p += cols;
        }
        // Broadcast the flattened array
        MPI_Bcast(buffer, rows * cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        // Free the buffer memory
        free(buffer);
    } else {
        // Allocate memory for the 1D array
        auto *buffer = (double *) malloc(rows * cols * sizeof(double));
        // Broadcast the flattened array
        MPI_Bcast(buffer, rows * cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        // Allocate memory for the 2D array
        *array = (double **) malloc(rows * sizeof(double *));
        for (int i = 0; i < rows; ++i) {
            (*array)[i] = (double *) malloc(cols * sizeof(double));
            memcpy((*array)[i], buffer + i * cols, cols * sizeof(double));
        }
        // Free the buffer memory
        free(buffer);
    }
}


int main(int argc, char **argv) {
    int rank, size;
    int strip_size_A, A_row, A_col, B_row, B_col;
    // **A is the matrix, *Adata is a flattened 1D of it.
    double **A, *Adata, **B, *Bdata, **strip_A, *stripdataA,
            **part, *partdata, **res, *resdata;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        cout << "This program calculates matrix multiplication (AxB): " << endl;
        cout << "Enter Number of Rows for A: " << endl;
        cin >> A_row;
        cout << "Enter Number of Columns for A: " << endl;
        cin >> A_col;
        cout << "Enter Number of Rows for B: " << endl;
        cin >> B_row;
        cout << "Enter Number of Columns for B: " << endl;
        cin >> B_col;

        if (A_col != B_row) {
            cerr << "A's column Number does NOT equal B's row Number... exiting." << endl;
            exit(-1);
        }

        if (A_row % size != 0) {
            cerr << "Matrix can NOT be parallelized" << endl;
            exit(-1);
        }

        /* calculate the strip size of A*/
        strip_size_A = A_row / size;

        /* initialize & generate values of Matrix A & B */
        initializeMatrix(A, Adata, A_row, A_col);
        initializeMatrix(B, Bdata, B_row, B_col);
        for (int i = 0; i < A_row; i++) {
            for (int j = 0; j < A_col; j++) {
                A[i][j] = i * j;
            }
        }
        for (int i = 0; i < B_row; i++) {
            for (int j = 0; j < B_col; j++) {
                B[i][j] = i * j;
            }
        }
    }

    /* Begin Time Calculation */
    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    /* Broadcasting */
    MPI_Bcast(&A_row, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&A_col, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&B_row, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&B_col, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&strip_size_A, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /* Broadcast B as a whole matrix */
    broadcastMatrix(&B, B_row, B_col, rank);

    /* Initialize Matrix strip_A, part, and res */
    initializeMatrix(strip_A, stripdataA, strip_size_A, A_col);
    initializeMatrix(part, partdata, strip_size_A, B_col);
    initializeMatrix(res, resdata, A_row, B_col);

    /* Scatter Matrix A to strip_A properly */
    MPI_Scatter(Adata, A_col * strip_size_A,
                MPI_DOUBLE, &(strip_A[0][0]),
                A_col * strip_size_A,
                MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* Do the operation for the subMatrices */
    MultiplyMatrices(strip_A, B, part, strip_size_A, A_col, B_col);

    /* Gather subResults into the master node */
    MPI_Gather(&(part[0][0]), strip_size_A * B_col, MPI_DOUBLE,
               resdata, strip_size_A * B_col,
               MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* End Time */
    double end = MPI_Wtime();

    if (rank == 0) {
        cout << "Matrix A: " << endl;
        printMatrix(A, A_row, A_col);
        cout << "Matrix B: " << endl;
        printMatrix(B, B_row, B_col);
        cout << "Matrix AxB: " << endl;
        printMatrix(res, A_row, B_col);
        cout << "Time: " << (end - start) * 1000 << " ms" << endl;
    }
    MPI_Finalize();
    return 0;
}
