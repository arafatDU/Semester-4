#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include <unistd.h>
#include<semaphore.h>
#define n 1
#define n1 50
int status[n];
int b=0;
sem_t mutex;
sem_t barber;
void *barb()
{
printf("Barber Sleeping\n");
b=1;
sem_wait(&barber);
printf("Barber woke up\n");
sleep(1);
b=0;
}
void *handler(void *ptr)
{
int x; 
    x = *((int *) ptr);
int flag=0;
int i=0;
int cnt=0;
for(i=0;i<n;i++)
{
    if(status[i]==1)
    {
    flag=1;
    cnt++;      
    }
}
printf("Count=%d",cnt);
if(cnt==n)
{
    printf("%d Customer Returned\n",x);
    return 0;
}
if(flag==1)
{
    status[x]=1;
    printf("%d Customer waiting\n",x); 
    sem_wait(&mutex);
}
if(b==1)
{
    printf("Customer %d woke up barber",x);
    sem_post(&barber);
}   
printf("Cutting Hair of customer %d\n",x);
status[x]=1;
sleep(5);
flag=0;
for(i=0;i<n;i++)
{
    if(status[i]==1)
    {
        flag=1;     
    }
}
status[x]=0;
printf("Finished cutting Hair of customer %d\n",x);
if(flag==1) 
sem_post(&mutex);
}
int main()
{
sem_init(&mutex, 0, n);
sem_init(&barber, 0, 1);
pthread_t thread[n1];
pthread_t barber;
int i=0;
for(i=0;i<n;i++)
{
    status[i]=0;
}

pthread_create(&barber,NULL,barb,NULL);
pthread_join(barber,NULL);
for(i=0;i<n1;i++)
{
    sleep(1);
    printf("Customer entered %d\n",i);
    pthread_create(&thread[i], NULL, handler, (void *)&i);
    //pthread_join(thread[i],NULL);
}
for(i=0;i<n1;i++)
{
    //pthread_join(thread[i],NULL);
}
//sem_post(&barber);
}