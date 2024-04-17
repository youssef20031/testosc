#define _GNU_SOURCE // Needed for CPU affinity macros
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For sleep()
#include <sched.h>  // For CPU affinity functions

#define NUM_THREADS 4
#define DELAY_ITERATIONS 1000000

// Struct to hold thread information
struct ThreadInfo {
    pthread_t thread_id;
    int thread_num;
    int sched_policy;  // Added: Scheduling policy (e.g., SCHED_RR)
    int priority;     // Added: Scheduling priority
};

// Function to be executed by each thread
void *thread_function(void *arg) {
    struct ThreadInfo *info = (struct ThreadInfo *)arg;
    int thread_num = info->thread_num;
    pthread_t id = info->thread_id;

    printf("Thread %d started with pid %lu.\n", thread_num, (unsigned long)id);
    for (int i = 0; i < DELAY_ITERATIONS; ++i) {
        // Simulate some work
    }
    printf("Thread %d is working with pid %lu.\n", thread_num, (unsigned long)id);
    for (int i = 0; i < DELAY_ITERATIONS; ++i) {
        // Simulate some more work
    }
    printf("Thread %d finished with pid %lu.\n", thread_num, (unsigned long)id);

    pthread_exit(NULL);
}

int main() {
    struct ThreadInfo threads[NUM_THREADS]; // Array of thread information

    // Set scheduling policy and priority for main thread (optional)
    // ... (if needed)

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads[i].thread_num = i;
        if (pthread_create(&threads[i].thread_id, NULL, thread_function, &threads[i]) != 0) {
            perror("pthread_create failed");
            return 1;
        }

        // Set scheduling policy and priority for each thread (optional)
         threads[i].sched_policy = SCHED_FIFO;  // Example: Set to Round Robin
         threads[i].priority = 1;           // Example: Set priority to 1
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i].thread_id, NULL) != 0) {
            perror("pthread_join failed");
            return 1;
        }
    }

    printf("All threads finished.\n");
    return 0;
}
