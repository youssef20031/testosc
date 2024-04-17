#define _GNU_SOURCE  // Needed for CPU affinity macros
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // For sleep()
#include <sched.h>   // For CPU affinity functions

#define NUM_THREADS 4
#define DELAY_ITERATIONS 1000000

// Struct to hold thread function arguments
struct ThreadArgs {
    int thread_id;
    pthread_attr_t *attr;
};

// Function to be executed by each thread
void *thread_function(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    int thread_id = args->thread_id;
    pthread_t id = pthread_self();

    // Set CPU affinity for the current thread
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);  // Set affinity to core 0
    pthread_setaffinity_np(id, sizeof(cpu_set_t), &cpuset);

    printf("Thread %d started with pid %lu.\n", thread_id, (unsigned long)id);
    for (int i = 0; i < DELAY_ITERATIONS; ++i) {
        // Simulate some work
    }
    printf("Thread %d is working with pid %lu.\n", thread_id, (unsigned long)id);
    for (int i = 0; i < DELAY_ITERATIONS; ++i) {
        // Simulate some more work
    }
    printf("Thread %d finished with pid %lu.\n", thread_id, (unsigned long)id);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    struct ThreadArgs thread_args[NUM_THREADS]; // Array of thread arguments
    pthread_attr_t attr[NUM_THREADS]; // Array of attributes

    // Create threads with specified CPU affinity and scheduling policy
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].thread_id = i;
        pthread_attr_init(&attr[i]); // Initialize each attribute
        pthread_attr_setinheritsched(&attr[i], PTHREAD_EXPLICIT_SCHED); // Set to use explicitly set scheduling attributes
        pthread_attr_setschedpolicy(&attr[i], SCHED_RR);

        // Set scheduling priority
        struct sched_param param;
        param.sched_priority = 1; // Set priority to 1
        pthread_attr_setschedparam(&attr[i], &param);

        thread_args[i].attr = &attr[i]; // Pass a pointer to the attribute

        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join failed");
            return 1;
        }
    }

    printf("All threads finished.\n");
    return 0;
}
