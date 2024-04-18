#include <iostream>
#include <mpich/mpi.h>

using namespace std;

int main(int argc, char *argv[]) {
    int rank, size;
    int user_input;
    int sum = 0;
    int ratio, total;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        // Rank 0 collects user input
        printf("Enter a number: ");
        scanf("%d", &user_input); // NOLINT(*-err34-c)
    }
    // Broadcast user input to all processes
    MPI_Bcast(&user_input, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (user_input % size != 0) {
        if (rank == 0) {
            cout << "Can't divide processes" << endl;
        }
        exit(0);
    }
    ratio = user_input / size;
    for (int i = ratio * rank + 1; i <= ratio * rank + ratio; i++) {
        sum += i;
    }
    MPI_Reduce(&sum, &total, 1, MPI_INT, MPI_SUM,
               0, MPI_COMM_WORLD);
    if (rank == 0) {
        cout << "Total sum is: " << total << endl;
    }
    MPI_Finalize();
    return 0;
}