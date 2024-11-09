#include "matrixMul.h"
#include <stdlib.h>

int main() {
    // Static allocation of matrices
    int A[N][N];
    int B[N][N];
    int C[N][N];
    int randA = rand() % 10;
    int randB = rand() % 10;

    printf("Matrices allocated successfully.\n");

    // Initialize matrices A and B
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = randA;
            B[i][j] = randB;
            C[i][j] = 0;
        }
    }
    
    printf("Matrices initialized successfully.\n");
    
    printf("Matrix A looks like this.\n");
    //displayMatrix(A);

    printf("Matrix B looks like this.\n");
    //displayMatrix(B);

    printf("Now we multiply them together.\n\n");
    matrixMultiply(A, B, C);

    printf("Matrix multiplication complete!\n");

    // Display the resulting matrix C
    printf("Resulting Matrix C:\n");
    //displayMatrix(C);
    printf("%d", N);

    return 0;
}
