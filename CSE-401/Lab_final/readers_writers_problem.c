#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_READERS 5
#define NUM_WRITERS 1

sem_t mutex, rw_mutex;
int readers_count = 0;

int shared_data;

void init_semaphores();
void *reader(void *arg);
void *writer(void *arg);
void destroy_semaphores();

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    
    // Initialize semaphores
    init_semaphores();
    
    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    
    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    
    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    
    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    
    // Destroy semaphores
    destroy_semaphores();
    
    return 0;
}

void init_semaphores(){
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
}

void *reader(void *arg) {
    int id = *(int *)arg;

    // int id = *(int *)arg;
    
    while (1) {
        // Entering critical section

        sem_wait(&mutex); // acquiring the mutex lock to increment the readers_count variable
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&rw_mutex); // acquiring the rw_mutex lock to read the value of the shared object, Block writers if it's the first reader
        }
        sem_post(&mutex); // releasing the mutex lock after incrementing

        printf("Reader %d reads the value of the shared data as: %d,when readers count is %d\n", id, shared_data, readers_count);

        // Exiting critical section
        sem_wait(&mutex); // acquiring the mutex lock again to decrement the readers_count variable
        readers_count--;
        if (readers_count == 0) {
            sem_post(&rw_mutex); // releasing the rw_mutex after reading the value, now it unblocks the waiting writers as there is no readers
        }
        sem_post(&mutex); // releasing the mutex lock after decrementing 

        // Simulate reading time
        sleep(rand()%5);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    
    while (1) {
        // Entering critical section
        sem_wait(&rw_mutex); // acquiring rw_mutex lock to gain exclusive access
        
        shared_data = rand() % 100; // writes the value into the shared object

        printf("Writer %d writes the value %d in the shared data\n", id, shared_data);
        
        // Exiting critical section
        sem_post(&rw_mutex); // Release the rw_mutex

        // Simulate writing time
        sleep(rand()%5);
    }
    return NULL;
}

void destroy_semaphores(){
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
}