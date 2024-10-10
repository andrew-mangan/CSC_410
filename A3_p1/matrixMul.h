#include <stdio.h>

#define N 50 // Size of the matrices



void displayMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; ++i) {
        printf("{ ");
        for (int j = 0; j < N; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("}\n");
    }
}

