#include<stdio.h>

#define N 5

int main()
{
    int process[N] = {1, 2, 3, 4, 5};
    int arivalT[N] = {0, 0, 0, 0, 0};
    int burstT[N] = {2, 1, 8, 4, 5};
    int priority[N] = {2, 1, 4, 2, 3};

    int completeT[N], turnaroundT[N], waitingT[N], sum=0, avgTT=0, avgWT=0;

    for(int i=0; i<N; i++){
        sum += arivalT[i] + burstT[i];
        completeT[i] = sum;
        turnaroundT[i] = completeT[i] - arivalT[i];
        waitingT[i] = turnaroundT[i] - burstT[i];
    }

    for(int i=0; i<N; i++) printf("|--- P%d ---|", i+1);
    printf("\n0");
    for(int i=0; i<N; i++) printf("          %d", completeT[i]);
    printf("\n");


    printf("\nProcess   A.T    B.T    Priority  C.T   T.T    W.T\n");
    for(int i=0; i<N; i++){
        printf("   P%d\t   %d\t   %d\t    %d\t   %d\t  %d\t %d\t\n", process[i], arivalT[i], burstT[i], priority[i], completeT[i] ,turnaroundT[i], waitingT[i]);
    }


    for(int i=0; i<N; i++){
        avgTT += turnaroundT[i];
        avgWT += waitingT[i];
    }
    printf("\nAverage Turnaround Time = %d\n", avgTT/N);
    printf("\nAverage Waiting Time = %d\n", avgWT/N);

    return 0;
}