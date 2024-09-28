#include <stdio.h>
#include <pthread.h>

#define SIZE 1000000
#define NUM_THREADS 0

int arr[SIZE];
long partialSums[NUM_THREADS] = {0}; // Array to store partial sums for each thread

// Entry function for each thread
void* sumPart(void* arg) {
    // Divide the work for each thread based on their id and let them compute partial sums
    int thread_ids = *(int*)arg;
    int start = thread_ids * (SIZE / NUM_THREADS);  // Define range start (start from 2)
    int end = (thread_ids + 1) * (SIZE / NUM_THREADS);  // Define range end
    long partialSum = 0;
    
    for(int i = start; i < end; i++)
    {
        partialSum = partialSum + arr[i];
    }

    partialSums[thread_ids] = partialSum;

        
    return NULL;
}

int main() {

    // Initialize the array
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1; 
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads to compute partial sums
        // ------> Write your code here
for (int i = 0; i < NUM_THREADS; i++){
    thread_ids[i] = i;
    pthread_create(&threads[i], NULL, sumPart, &thread_ids[i]);
}       
    // Wait for all threads to finish
        // -------> Write your code here
for (int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);

}
    // Combine the partial sums from all threads
    long totalSum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        totalSum += partialSums[i];
    }

    printf("Total Sum: %lu\n", totalSum);
    printf("partial sum 0: %lu \n", partialSums[0]);
    printf("partial sum 1: %lu \n", partialSums[1]);
    printf("partial sum 2: %lu \n", partialSums[2]);
    printf("partial sum 3: %lu \n", partialSums[3]);

    return 0;
}
