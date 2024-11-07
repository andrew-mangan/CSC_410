#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 800 // Size of the matrices



void displayMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; ++i) {
        printf("{ ");
        for (int j = 0; j < N; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("}\n");
    }
}

void matrixMultiply(int A[N][N], int B[N][N], int C[N][N]) {
    int num_threads = 1;
    omp_set_num_threads (num_threads);

    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int start = thread_num * (N / num_threads);
        int end = ((thread_num + 1) * (N / num_threads));

        printf("thread number %i starts at %i and ends at %i.\n", thread_num, start, end);
    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
           
             for (int k = 0; k < N; k++) {
                C[i][j] = A[i][k] * B[k][j];
            }
 
            //printf("%d", C[i][j]);
        }
    }
        
    }

    
    }