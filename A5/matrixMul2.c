#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 1000000

void multiply_matrices(int *A, int *B, int *C, int n, int start, int end) { //multiply A and B
    for (int i = start; i < end; i++) {
        for (int j = 0; j < n; j++) {
            C[i * N + j] = 0;  // Initialize the element
            for (int k = 0; k < n; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

int main(int argc, char **argv) {
    int rank, procs;

    int *A = NULL;
    //int *B = NULL;
    int *C = NULL;
    int *C_local = NULL;
    int *A_local = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);

    int rows_per_proc = N / procs;
    int start = rank * rows_per_proc;
    int end = start + rows_per_proc;

    // Dynamically allocate memory for the matrices
    int* local_A = (int*)malloc(rows_per_proc * N * sizeof(int*));
    int* B = (int*)malloc(N * N * sizeof(int*));
    int* local_C = (int*)malloc(rows_per_proc * N * sizeof(int*));


    if (rank == 0) {
        // Allocate matrices A and B
        A = (int*)malloc(N * sizeof(int));
        B = (int*)malloc(N * sizeof(int));
        C = (int*)malloc(N * sizeof(int));

        // Initialize matrix A
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
            A[i * N + j] = 2; 
            B[i * N + j] = 3;
            C[i * N + j] = 0; 
        }
        }


    }

    // Broadcast matrix B to all processe
    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);


    // Scatter rows of matrix A to all processes
    A_local = malloc(N / procs * N * sizeof(int));
    MPI_Scatter(A, rows_per_proc * N, MPI_INT, local_A, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform local multiplication
    multiply_matrices(A_local, B, C_local, N / procs, start, end);

    // Gather results from all processes
    if (rank == 0) {
        MPI_Gather(C, N * N / procs, MPI_INT, C, N * N / procs, MPI_INT, 0, MPI_COMM_WORLD);
        
        // Print the resulting matrix C
        printf("Resulting Matrix C:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", C[i * N + j]);
            }
            printf("\n");
        }

        // Free the allocated memory
        free(A);
        free(B);
        free(C);
    } else {
        MPI_Gather(C, N * N / procs, MPI_INT, C, N * N / procs, MPI_INT, 0, MPI_COMM_WORLD);
        free(B);
    }

    // Free local memory
    free(A_local);
    free(C_local);

    MPI_Finalize();
    return 0;
}