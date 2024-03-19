#include <mpich/mpi.h>
#include <cmath>

using namespace std;

double trapQuad(double a, double b, int n) {
    double N = n;
    double h = (b - a) / N;
    double I = (h / 2) * ((pow(a, 2) + pow(b, 2)));
    for (double i = a + h; i < b; i += h) { // NOLINT(*-flp30-c)
        I += h * pow(i, 2);
    }
    return I;
}

int main(int argc, char *argv[]) {
    int rank, size;
    double part_sum, total, divide, b, a;
    a = 0.0, b = 10.0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    divide = (b - a) / size;
    total = part_sum = trapQuad(a + rank * divide, a + (rank + 1) * divide, 1000000);
    if (rank != 0) {
        MPI_Send(&part_sum, 1, MPI_DOUBLE,
                 0, 21, MPI_COMM_WORLD);
    } else {
        for (int i = 1; i < size; i++) {
            MPI_Recv(&part_sum, 1, MPI_DOUBLE,
                     i, 21, MPI_COMM_WORLD, &status);
            total += part_sum;
        }
        printf("Integration is: %f\n", total);
    }
    MPI_Finalize();
    return 0;
}