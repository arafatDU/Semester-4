#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int lock = 0;

void *producer(void *param) {
    
    int item;
    while (1) {
        
        item = rand() % 100;

        while(in == BUFFER_SIZE)
        {
           printf("Buffer is full!\n");
           sleep(2);
        }
        
        while(lock);
        
        lock = 1;
        
        buffer[in] = item;
        printf("Item %d is produced\n",item);
        in = (in + 1) % BUFFER_SIZE;
        
        lock = 0;
           
        sleep(2);
        
    }
    
}

void *consumer(void *param) {
    
       int item;
       while (1) {
        
        sleep(3);

        while(in == 0)
        {
           printf("Buffer is empty!\n");
           sleep(2);
        }
        
        while(lock);
        
       
        lock = 1;
        
        item = buffer[out] ;      
        
        
        printf("Item %d is consumed\n",item);
        out = (out + 1) % BUFFER_SIZE;
        
        lock = 0;
        
        sleep(2);
        
}
}

int main() {

    srand(time(NULL));

    pthread_t producer_thread, consumer_thread;

    
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
