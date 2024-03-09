#include <mpich/mpi.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsequenced"
using namespace std;

int main(int argc, char *argv[]) {
    int myRank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (myRank == 0) {
        printf("Processor %d of %d: Master Node!\n", myRank, size);
    } else if (myRank % 2 == 0) {
        printf("Processor %d of %d: Even Worker Node!\n", myRank, size);
    } else {
        printf("Processor %d of %d: Odd Worker Node!\n", myRank, size);
    }
    MPI_Finalize();
    return 0;
}

#pragma clang diagnostic pop