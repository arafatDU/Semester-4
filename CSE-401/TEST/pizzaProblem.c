#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<semaphore.h>
#include<pthread.h>

#define true 1
#define false 0

int num_student;
int num_slices = 0;
int S;
sem_t pizza;    
sem_t deliver;
sem_t mutex;
int deliveryProcess = true;

void *student(void *arg);
void *delivery(void *arg);
void init_sem();
void destroy_sem();

int main(){
    srand(time(NULL));
    
    init_sem();
    
    printf("Enter number of stuents: ");
    scanf("%d", &num_student);
    printf("Enter number of slices: ");
    scanf("%d", &S);
    printf("\n");

    pthread_t students[num_student];
    pthread_t pizza_delivery;
    int studentID[num_student];
    
    for(int i = 0; i < num_student; i++){
        studentID[i] = i + 1;
    }
    
    for(int i = 0; i < num_student; i++){
        pthread_create(&students[i], NULL, student, &studentID[i]);
    }
    
    pthread_create(&pizza_delivery, NULL, delivery, NULL);
    
    for(int i = 0; i < num_student; i++){
        pthread_join(students[i], NULL);
    }
    
    pthread_join(pizza_delivery, NULL);
    
    destroy_sem();
}

void init_sem(){
    sem_init(&pizza, 0, 0);
    sem_init(&deliver, 0, 1);
    sem_init(&mutex, 0, 1);
}

void destroy_sem(){
    sem_destroy(&pizza);
    sem_destroy(&deliver);
    sem_destroy(&mutex);
}

void *student(void *arg){
    int id = *(int *)arg;
    int flag;
    while(1){
        flag = true;
        while(num_slices == 0){
            if(flag){
                printf("Student %d is sleeping\n\n", id);
                flag = false;
            }
        }
        sem_wait(&mutex);
        if(num_slices > 0){
            num_slices--;
            sem_wait(&pizza);
            printf("Student %d is eating and studying. Remaining slices: %d\n\n", id, num_slices);
        } 
        // sem_post(&mutex);
        // sem_wait(&mutex);
        if(num_slices == 0){
            if(!deliveryProcess){
                deliveryProcess = true;
                sem_post(&deliver);
            }
        }
        sem_post(&mutex);
        sleep((rand() % 3) + 1);
    }
}

void *delivery(void *arg){
    while(1){
        sem_wait(&deliver);

        printf("Pizza is being prepared.....\n\n");
        sleep(5);
        printf("Pizza is delivered\n\n");
        sem_wait(&mutex);
        num_slices += S;
        sem_post(&mutex);
        for(int i = 0; i < S; i++){
            sem_post(&pizza);
        }
        deliveryProcess = false;
    }
}
