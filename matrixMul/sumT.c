#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 1000
#define NUM_THREADS 7


long long arr[SIZE];
long long totalSum = 0;
pthread_mutex_t lock;
pthread_cond_t cond;

void* sumPart(void* arg) {
    int thread_id = *(int*)arg;
    int chunk_size = SIZE / NUM_THREADS;
    int start = thread_id * chunk_size;
    int end = (thread_id + 1) * chunk_size;

    long long temp;
    // Calculate partial sums
    
    printf("Thread %i shows start %i, and stop %i with Sum: %lld\n", start, end, thread_id, totalSum);
    pthread_mutex_lock(&lock);
    for (int i = start; i < end; i++) {
        pthread_cond_signal(&cond);
        totalSum += arr[i];
        // sleep(rand()%2);
        
    }
    pthread_mutex_unlock(&lock);
    
    return NULL;
}

int main() {
    // Initialize the array
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1; 
    }

    // srand(time(NULL));
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads to compute partial sums
    //pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        printf("Thread %i shows Total Sum: %lld\n", i, totalSum);
        pthread_create(&threads[i], NULL, sumPart, &thread_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the total sum;
    printf("Total Sum: %lld\n", totalSum);

    //pthread clean up
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
