#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

#define N 1000000000 // intervals

double f(double x) {
    return 4.0 / (1.0 + x * x); // Function to integrate
}

double trapezoidalRule() {
    double h = 1.0 / N; 
    double sum = 0.5 * (f(0) + f(1)); 
    for (int i = 1; i < N; ++i) {
        sum += f(i * h);
    }
    sum *= h; 
    return sum;
}

int main(int argc, char *argv[]) {
    int rank, size;
    double a = 0.0, b = 1.0;  // Integration limits
    long long n = 1000000;     // Number of trapezoids
    double local_a, local_b, h;
    double local_sum = 0.0, total_sum = 0.0;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Calculate the step size
    h = (b - a) / n;

    // Divide the interval [a, b] into subintervals for each process
    long long local_n = n / size;
    local_a = a + rank * local_n * h;
    local_b = local_a + local_n * h;

    // Calculate the local sum for the trapezoidal rule
    for (long long i = 0; i < local_n; i++) {
        double x1 = local_a + i * h;
        double x2 = x1 + h;
        local_sum += (f(x1) + f(x2)) * h / 2.0;
    }

    // Use MPI_Reduce to sum up the local results and get the total sum at root
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Only the root process will calculate and print the final result
    if (rank == 0) {
        // Multiply the result by 4 to get the approximation of Pi
        double pi_estimate = total_sum * 4.0;
        printf("Estimated Pi = %f\n", pi_estimate);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
