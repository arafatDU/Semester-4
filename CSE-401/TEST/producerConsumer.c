#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define SIZE 5

sem_t full, empty, mutex;
int buffer[SIZE], produced = 0, consumed = 0, in = 0, out = 0;


void *producer(void *param){
  int item;
  while(1){
    item = rand() % 100;
    sem_wait(&empty);
    sem_wait(&mutex);
    buffer[in] = item;
    produced++;
    in = (in + 1) % SIZE;
    printf("Producer produced item %d\n", item);
    sem_post(&mutex);
    sem_post(&full);
    sleep(1);
  }
}

void *consumer(void *param){

  while(1){
    sem_wait(&full);
    sem_wait(&mutex);
    int item = buffer[out];
    consumed++;
    printf("Consumer consumed item %d\n", item);
    out = (out + 1) % SIZE;
    sem_post(&mutex);
    sem_post(&empty);
    sleep(2);
  }
}


int main(){
  pthread_t producer_thread, consumer_thread;
  sem_init(&mutex, 0, 1);
  sem_init(&empty, 0, SIZE);
  sem_init(&full, 0, 0);

  pthread_create(&producer_thread, NULL, producer, NULL);
  pthread_create(&consumer_thread, NULL, consumer, NULL);

  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);
  return 0;
}