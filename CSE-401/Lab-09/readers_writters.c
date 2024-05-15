#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define READERS_NUMBER 10
#define WRITERS_NUMBER 5

sem_t rw_semaphore , semaphore;
int count = 0 ;

void *writer(void *arg) {

    int id = *((int*)arg);
    
    while (1) {
        sem_wait(&rw_semaphore);

        printf("Writer %d is writing\n", id);
        
        sleep(1);

        sem_post(&rw_semaphore);

        sleep(2);
    }
   
}

void *reader(void *arg) {

    int id = *((int*)arg);
    
    while (1) {
        sem_wait(&semaphore);
        count++;
        if (count == 1) {
            sem_wait(&rw_semaphore);
        }
        sem_post(&semaphore);

        
        printf("Reader %d is reading\n", id);
        
        sleep(1);

       // sem_wait(&semaphore);
        
        count--;
        
        if (count == 0) {
            sem_post(&rw_semaphore);
        }
        sem_post(&semaphore);

        
        sleep(1);
    }
    
}


int main()
{
   pthread_t readers[READERS_NUMBER] , writers[WRITERS_NUMBER] ;
   
   int reader_ids[READERS_NUMBER] , writer_ids[WRITERS_NUMBER];
   
   sem_init(&semaphore,0,1);
   
   sem_init(&rw_semaphore,0,1);
   
   for (int i = 0; i < READERS_NUMBER; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

  
    for (int i = 0; i < WRITERS_NUMBER; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    
    for (int i = 0; i < READERS_NUMBER; ++i) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < WRITERS_NUMBER; ++i) {
        pthread_join(writers[i], NULL);
    }
   
   sem_destroy(&semaphore);
   
   sem_destroy(&rw_semaphore);
}