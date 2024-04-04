#include <mpich/mpi.h>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    int rank, size, number_of_tosses, number_in_circles = 0;

    double calc;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        cout << "Enter the number of tosses:" << endl;
        cin >> number_of_tosses;
        for (int i = 1; i < size; i++) {
            MPI_Send(&number_of_tosses, 1,
                     MPI_INT, i, 21, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&number_of_tosses, 1, MPI_INT,
                 0, 21, MPI_COMM_WORLD, &stat);
    }
    random_device rd;
    mt19937 gen(rd());

    // Define a distribution for double values between -1 and 1/
    uniform_real_distribution<double> dist(-1.0, 1.0);
    double ratio = number_of_tosses / (double) size;
    auto start = high_resolution_clock::now();
    for (double i = ratio * rank; i < ratio * (rank + 1); i++) { // NOLINT(*-flp30-c)
        double x = dist(gen);
        double y = dist(gen);
        double sq_dis = x * x + y * y;
        if (sq_dis <= 1) {
            number_in_circles++;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    auto time = duration.count();
    auto totalTime = time;
    calc = (double) number_in_circles;
    if (rank != 0) {
        MPI_Send(&number_in_circles, 1,
                 MPI_INT, 0, 22, MPI_COMM_WORLD);
        MPI_Send(&time, 1,
                 MPI_LONG, 0, 23, MPI_COMM_WORLD);
    } else {
        for (int i = 1; i < size; i++) {
            MPI_Recv(&number_in_circles, 1,
                     MPI_INT, i, 22, MPI_COMM_WORLD, &stat);

            MPI_Recv(&time, 1,
                     MPI_LONG, i, 23, MPI_COMM_WORLD, &stat);
            calc += number_in_circles;
            totalTime += time;
        }
        cout << "PI: " << 4 * (calc) / number_of_tosses << endl;
        cout << "Time: " << totalTime << " ns." << endl;
    }
    MPI_Finalize();
    return 0;
}