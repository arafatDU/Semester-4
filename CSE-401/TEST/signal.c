#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

// Global variable to indicate if the program should continue running
volatile sig_atomic_t keep_running = 1;
pthread_t worker_thread;

// Function prototypes
void sigint_handler(int sig);
void* worker_task(void* arg);

int main() {
    // Set up the SIGINT signal handler
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Create the worker thread
    if (pthread_create(&worker_thread, NULL, worker_task, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Main thread waits for the worker thread to finish
    pthread_join(worker_thread, NULL);

    printf("Main program terminating.\n");

    return 0;
}

// Signal handler for SIGINT
void sigint_handler(int sig) {
    printf("\nSIGINT caught! Terminating the program.\n");
    keep_running = 0;
    pthread_cancel(worker_thread); // Cancel the worker thread
}

// Function executed by the worker thread
void* worker_task(void* arg) {
    while (keep_running) {
        printf("Worker thread is running...\n");
        sleep(1); // Simulate some work
    }
    printf("Worker thread terminating.\n");
    return NULL;
}
