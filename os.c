#define _GNU_SOURCE  // Needed for CPU affinity macros
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // For sleep()
#include <sched.h>   // For CPU affinity functions

#define NUM_THREADS 4
#define DELAY_ITERATIONS 1000000000

// Function to be executed by each thread
void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    pthread_t id = pthread_self();
    printf("Thread %d started with pid %lu.\n", thread_id, (unsigned long)id);
    for (int i = 0; i < DELAY_ITERATIONS; ++i) {

    }  // Simulate some work
    printf("Thread %d is working with pid %lu.\n", thread_id, (unsigned long)id);
    for (int i = 0; i < DELAY_ITERATIONS; ++i) {

    }    // Simulate some more work
    printf("Thread %d finished with pid %lu.\n", thread_id, (unsigned long)id);
    for (int i = 0; i < DELAY_ITERATIONS; ++i) {

    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);  // Set affinity to core 0

    // Create threads with specified CPU affinity
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        //pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        //pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
        pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
        if (pthread_create(&threads[i], &attr, thread_function, &thread_ids[i])!= 0) {
            perror("pthread_create failed");
            return 1;
        } else {
             for (int j = 0; j < 5*i; ++j) {

            	}
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
