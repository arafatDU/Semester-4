#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define SIZE 5


sem_t full,empty,mutex;
int buffer[SIZE], produced=0,consumed=0,in=0,out=0;

void *producer_func(void *param)
{
    while(1)
    {
        int item = rand() % 100;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in]=item;
        in = (in+1)%SIZE;
        produced++;
        printf("Produced %d\n",item);
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
}

void *consumer_func(void *param)
{
    while(1)
    {
        sem_wait(&mutex);
        sem_wait(&full);
        int item = buffer[out];
        printf("Consumed %d\n",item);
        out = (out+1)%SIZE;
        consumed++;
        sem_post(&mutex);
        sem_post(&empty);
        sleep(2);
    }
}
int main()
{
    pthread_t producer, consumer;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);


    pthread_create(&producer, NULL, producer_func, NULL);

    pthread_create(&consumer, NULL, consumer_func, NULL);


    pthread_join(producer, NULL);
    
    pthread_join(consumer, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}