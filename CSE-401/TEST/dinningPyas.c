#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

int philNum, chopNum;
sem_t chopsticks[2];

void *eat(void *arg);

int main(){
    srand(time(NULL));
    printf("Enter number of philosophers: ");
    scanf("%d", &philNum);
    printf("\n");
    chopNum = philNum;
    chopsticks[philNum];
    pthread_t philosopers[philNum];
    int philID[philNum];
    for(int i = 0; i < philNum; i++){
        philID[i] = i + 1;
    }
    for(int i = 0; i < chopNum; i++){
        sem_init(&chopsticks[i], 0, 1);
    }
    for(int i = 0; i < philNum; i++){
        pthread_create(&philosopers[i], NULL, eat, &philID[i]);
    }
    for(int i = 0; i < philNum; i++){
        pthread_join(philosopers[i], NULL);
    }
    return 0;
}

void *eat(void *arg){
    int num = *(int *)arg;
    while(1){
        int left = num;
        int right = ( num  == philNum ) ? (num + 1) % philNum : num + 1;
        printf("Philosopher %d is thinking.....\n\n", num);
        sleep((rand() % 3) + 1);
        printf("Philosopher %d is hungry\n\n", num);
        if(num == philNum){
            sem_wait(&chopsticks[num % philNum]);
            sem_wait(&chopsticks[num - 1]);
        }
        else{
            sem_wait(&chopsticks[num - 1]);
            sem_wait(&chopsticks[num % philNum]);
        }
        printf("Philosopher %d has taken chopsticks %d and %d\n\n", num, left, right);
        printf("Philosopher %d is eating.....\n\n", num);
        sleep((rand() % 2) + 1);
        printf("Philosopher %d has finihed eating\n\n", num);
        sem_post(&chopsticks[num - 1]);
        sem_post(&chopsticks[num % philNum]);   
    }
}