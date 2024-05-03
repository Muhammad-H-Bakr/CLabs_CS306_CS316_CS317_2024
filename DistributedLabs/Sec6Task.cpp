#include <mpich/mpi.h>
#include <bits/stdc++.h>

using namespace std;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"


double maxValue(double **mat, int n, int m) {
    double max = mat[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] > max) {
                max = mat[i][j];
            }
        }
    }
    return max;
}

int main(int argc, char **argv) {
    int rank, size;
    int strip_size, A_row, A_col;
    double **A, **strip_A, *Adata, *stripdata, locMax, absMax;


    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        cout << "Enter Number of Rows: " << endl;
        cin >> A_row;
        cout << "Enter Number of Columns: " << endl;
        cin >> A_col;

        /* calculate the strip size */
        strip_size = A_row / size;

        /* generate Matrix A */
        Adata = (double *) malloc(sizeof(double) * A_row * A_col);
        A = (double **) malloc(sizeof(double *) * A_row);
        for (int i = 0; i < A_row; i++) {
            A[i] = &(Adata[i * A_col]);
        }
        for (int i = 0; i < A_row; i++) {
            for (int j = 0; j < A_col; j++) {
                A[i][j] = i * j;
            }
        }
    }
    
    /* Begin Time Calculation */
    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    /* Broadcasting the row, column size of Matrix A as well as strip size of Matrix B */
    MPI_Bcast(&A_row, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&A_col, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&strip_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    /* Initialize Matrix B */
    stripdata = (double *) malloc(sizeof(double) * strip_size * A_col);
    strip_A = (double **) malloc(sizeof(double *) * strip_size);
    for (int i = 0; i < strip_size; i++) {
        strip_A[i] = &(stripdata[i * A_col]);
    }

    /* Properly Scatter Matrix A to Matrices B */
    MPI_Scatter(Adata, A_col * strip_size,
                MPI_DOUBLE, &(strip_A[0][0]), A_col * strip_size,
                MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* Reduce & Done */
    locMax = maxValue(strip_A, strip_size, A_col);
    MPI_Reduce(&locMax, &absMax, 1,
               MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    /* End Time */
    double end = MPI_Wtime();
    if (rank == 0) {
        cout << "Matrix: " << endl;
        for (int i = 0; i < A_row; i++) {
            for (int j = 0; j < A_col; j++) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Absolute Max: " << absMax << endl
             << "Time: " << (end - start) * 1000 << "ms" << endl;
    }
    MPI_Finalize();
    return 0;
}

#pragma clang diagnostic pop
