#include <stdio.h>
#include <stdlib.h> 
#include <mpi.h>


#define N 10 

void displayMatrix(int** matrix, int n, int rank) {
if (rank == 0) { //print using process 0

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", matrix[i * N + j]);
        }
        printf("\n");
        }
    }
}

void matrixMultiply(int** A, int** B, int** C, int n, int rank, int start, int end) {

    for (int i = start; i < end; i++) {
        for (int j = 0; j < n; j++) {
            C[i * N + j] = 0;  // Initialize the element
            for (int k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

int main(int argc, char** argv) {

    int rank, procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int rows_per_proc = N / procs;
    int start = rank * rows_per_proc;
    int end = start + rows_per_proc;

    
    // Dynamically allocate memory for the matrices
    int* local_A = (int*)malloc(rows_per_process * N * sizeof(int*));
    int* B = (int*)malloc(N * N * sizeof(int*));
    int* local_C = (int*)malloc(rows_per_process * N * sizeof(int*));

    printf("Matrices allocated successfully.\n");

    // Initialize matrices A, B, and C
    if (rank == 0) { //print using process 0
    for (int i = 0; i < N; ++i) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] = (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));
    }
    }
    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }
    // Allocate 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = 2; 
            B[i * N + j] = 3; 
        }
    }
    }
    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(A, rows_per_process * N, MPI_INT, local_A, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);
   
    printf("Matrices initialized successfully.\n");

    matrixMultiply(A, B, C, N, rank, start, end);

    printf("Matrix multiplication complete!\n");

    MPI_Gather(C, N * N / procs, MPI_INT, C, N * N / procs, MPI_INT, 0, MPI_COMM_WORLD);

    //Optionally display the resulting matrix C

     printf("Resulting Matrix C:\n");
    //displayMatrix(C, N, rank);
    MPI_Finalize();
    // Free dynamically allocated memory
    for (int i = 0; i < N; ++i) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);


    
    return 0;
}
