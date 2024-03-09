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
    string ans;
    int myRank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    for (int i = myRank * 5; i < 5 * myRank + 5; i++) {
        ans.append(numberToString(i) + " ");
    }
    printf("Processor %d Display: %s\n", myRank, ans.c_str());
    MPI_Finalize();
    return 0;
}
