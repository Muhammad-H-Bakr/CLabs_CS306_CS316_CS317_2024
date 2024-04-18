#include <mpich/mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    int rank, size, min, elements, ratio, final;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        cout << "Enter the size of the array: ";
        cin >> elements;
    }
    MPI_Bcast(&elements, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (elements % size != 0) {
        if (rank == 0) {
            cout << "Indivisible size" << endl;
        }
        exit(0);
    }
    ratio = elements / size;
    int scat[ratio], arr[elements];
    if (rank == 0) {
        cout << "Enter the elements: " << endl;
        for (int i = 0; i < elements; i++) {
            cin >> arr[i];
        }
    }
    MPI_Scatter(&arr,
                ratio /*Number to be sent in each process == Receive number*/,
                MPI_INT, &scat, ratio /*Receive number*/,
                MPI_INT, 0, MPI_COMM_WORLD);
    min = scat[0];
    for (int i = 0; i < ratio; i++) {
        if (scat[i] < min) {
            min = scat[i];
        }
    }
    MPI_Reduce(&min, &final, 1,
               MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        cout << "Absolute min is: " << final << endl;
    }
    MPI_Finalize();
    return 0;
}