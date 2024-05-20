#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_STUDENTS 5
#define SLICES_PER_PIZZA 8

// Shared data
sem_t pizza;
sem_t deliver;
int num_slices = 0;
pthread_mutex_t mutex;

// Function prototypes
void *student(void *id);
void *delivery(void *arg);

int main() {
    pthread_t students[NUM_STUDENTS];
    pthread_t delivery_thread;
    int student_ids[NUM_STUDENTS];

    // Initialize semaphores and mutex
    sem_init(&pizza, 0, 0);
    sem_init(&deliver, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Create student threads
    for (int i = 0; i < NUM_STUDENTS; i++) {
        student_ids[i] = i + 1;
        pthread_create(&students[i], NULL, student, (void *)&student_ids[i]);
    }

    // Create delivery thread
    pthread_create(&delivery_thread, NULL, delivery, NULL);

    // Join student threads
    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(students[i], NULL);
    }

    // Cancel delivery thread (since we don't have a termination condition in this example)
    pthread_cancel(delivery_thread);
    pthread_join(delivery_thread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&pizza);
    sem_destroy(&deliver);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void *student(void *id) {
    int student_id = *(int *)id;

    while (1) {
        sem_wait(&pizza);

        pthread_mutex_lock(&mutex);
        if (num_slices > 0) {
            num_slices--;
            printf("Student %d is eating a slice of pizza. Slices left: %d\n", student_id, num_slices);
            pthread_mutex_unlock(&mutex);
        } else {
            pthread_mutex_unlock(&mutex);
            sem_post(&deliver);  // Order a new pizza
            sem_wait(&pizza);    // Wait for the new pizza to arrive
        }

        // Simulate time taken to study while eating
        sleep(rand() % 5 + 1);
    }

    return NULL;
}

void *delivery(void *arg) {
    while (1) {
        sem_wait(&deliver);  // Wait for an order

        printf("Delivery thread: Preparing and delivering a pizza...\n");
        sleep(2);  // Simulate time taken to prepare and deliver pizza

        pthread_mutex_lock(&mutex);
        num_slices = SLICES_PER_PIZZA;
        printf("Pizza delivered. Number of slices: %d\n", num_slices);
        for (int i = 0; i < SLICES_PER_PIZZA; i++) {
            sem_post(&pizza);  // Signal that a slice is available
        }
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}
