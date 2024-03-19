#include <iostream>
#include <mpich/mpi.h>
#include <sstream>

using namespace std;

string numberToString(int x) {
    ostringstream ss;
    ss << x;
    return ss.str();
}

int main(int argc, char *argv[]) {
    int rank, size, user_input, ratio, sum = 0, partial;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        cout << "Enter a number: " << endl;
        cin >> user_input;
        for (int i = 1; i < size; i++) {
            MPI_Send(&user_input, 1, MPI_INT,
                     i, 20, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&user_input, 1, MPI_INT,
                 0, 20, MPI_COMM_WORLD, &stat);
    }
    ratio = user_input / size;
    for (int i = ratio * rank + 1; i <= ratio * rank + ratio; i++) {
        sum += i;
    }
    partial = sum;
    if (rank != 0) {
        MPI_Send(&partial, 1, MPI_INT,
                 0, 21, MPI_COMM_WORLD);
    } else {
        for (int i = 1; i < size; i++) {
            MPI_Recv(&partial, 1, MPI_INT, i,
                     21, MPI_COMM_WORLD, &stat);
            sum += partial;
        }
        printf("Total sum is: %d\n", sum);
    }
    MPI_Finalize();
    return 0;
}