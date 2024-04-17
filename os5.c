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
    pthread_t thread_0, thread_1, thread_2, thread_3;
    struct ThreadArgs args[NUM_THREADS]; // Array of thread arguments

    // Create thread 0
    args[0].thread_id = 0;
    if (pthread_create(&thread_0, NULL, thread_function, &args[0]) != 0) {
        perror("pthread_create failed");
        return 1;
    }
    // Set scheduling policy and priority for thread 0
    struct sched_param param0, param1, param2, param3;
    param0.sched_priority = 1;
    param1.sched_priority = 1;
    param2.sched_priority = 1;
    param3.sched_priority = 1;

    // Create thread 1
    args[1].thread_id = 1;
    if (pthread_create(&thread_1, NULL, thread_function, &args[1]) != 0) {
        perror("pthread_create failed");
        return 1;
    }
    // Set scheduling policy and priority for thread 1

    // Create thread 2
    args[2].thread_id = 2;
    if (pthread_create(&thread_2, NULL, thread_function, &args[2]) != 0) {
        perror("pthread_create failed");
        return 1;
    }
    // Set scheduling policy and priority for thread 2

    // Create thread 3
    args[3].thread_id = 3;
    if (pthread_create(&thread_3, NULL, thread_function, &args[3]) != 0) {
        perror("pthread_create failed");
        return 1;
    }
    // Set scheduling policy and priority for thread 3
    pthread_setschedparam(thread_0, SCHED_RR, &param0);
    pthread_setschedparam(thread_1, SCHED_RR, &param0);
    pthread_setschedparam(thread_2, SCHED_RR, &param0);
    pthread_setschedparam(thread_3, SCHED_RR, &param0);

    // Wait for all threads to finish
    if (pthread_join(thread_0, NULL) != 0 || pthread_join(thread_1, NULL) != 0 ||
        pthread_join(thread_2, NULL) != 0 || pthread_join(thread_3, NULL) != 0) {
        perror("pthread_join failed");
        return 1;
    }

    printf("All threads finished.\n");
    return 0;
}
