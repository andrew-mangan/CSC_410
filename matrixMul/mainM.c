#include "matrixMul.h"
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100
#define NUM_THREADS 5

pthread_mutex_t lock;
pthread_cond_t cond;

 int A[SIZE][SIZE];
 int B[SIZE][SIZE];
 int C[SIZE][SIZE];

void* matrixMultiply(void* arg)
    {
    int thread_id = *(int*)arg;
    int start = thread_id * (SIZE / NUM_THREADS);  // Define range start (start from 2)
    int end = (thread_id+ 1) * (SIZE / NUM_THREADS);  // Define range end

    pthread_mutex_lock(&lock);
    for (int i = start; i < end; i++) {
        for (int j = start; j < end; j++) {
            //C[i][j] = 0;
            if ((C[i][j]) == NUM_THREADS){
                pthread_cond_signal(&cond);
            }
            for (int k = 0; k < N; k++) {
                C[i][j] = A[i][k] * B[k][j];
            }
 
        }
 
    }
    pthread_mutex_unlock(&lock);
    return NULL;

    }

int main() {
    // Static allocation of matrices

    int randA = rand() % 10 + 1;
    int randB = rand() % 10 + 1;
    
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    //pthread_mutex_init(&lock, NULL);

    printf("Matrices allocated successfully. Numbers used %i, and %i.\n", randA, randB);

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

    for(int i = 0; i < NUM_THREADS; i++){
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, matrixMultiply, &thread_ids[i]);
    }
    
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    for(int i = 0; i < NUM_THREADS; i++){
        
    }
    printf("Matrix multiplication complete!\n");

    // Display the resulting matrix C
    printf("Resulting Matrix C:\n");
    displayMatrix(C);

    //clean up thread controls
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
