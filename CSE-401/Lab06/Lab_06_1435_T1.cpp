#include<bits/stdc++.h>
using namespace std;

#define N 6

struct Process { 
    int pid; 
    int burstT;
    int arrivalT;
}; 


int main()
{
    int process[N] = {1, 2, 3, 4, 5, 6};
    int arivalT[N] = {0, 25, 30, 60, 100, 105};
    int burstT[N] = {20, 25, 25, 15, 10, 10};
    int priority[N] = {40, 30, 30, 35, 5, 10};

    int completeT[N], turnaroundT[N], waitingT[N], sum=0;
    float  avgTT=0, avgWT=0;
    

    Process Table[N];
    for(int i=0; i<N; i++){
        Table[i].pid = process[i];
        Table[i].burstT = burstT[i];
        Table[i].arrivalT = arivalT[i];
    }


    int remainT[n]; 
  
    
    for (int i = 0; i < n; i++) 
        remainT[i] = Table[i].bt; 
  
    int complete = 0, t = 0, minm = INT_MAX; 
    int shortest = 0, finish_time; 
    bool check = false; 
  
    
    while (complete != n) { 

        for (int j = 0; j < n; j++) { 
            if ((Table[j].art <= t) && 
            (remainT[j] < minm) && remainT[j] > 0) { 
                minm = remainT[j]; 
                shortest = j; 
                check = true; 
            } 
        } 
  
        if (check == false) { 
            t++; 
            continue; 
        } 
        remainT[shortest]--; 
        minm = remainT[shortest]; 
        if (minm == 0) 
            minm = INT_MAX; 

        if (remainT[shortest] == 0) { 
            complete++; 
            check = false; 

            finish_time = t + 1; 
            waitingT[shortest] = finish_time - 
                        Table[shortest].bt - 
                        Table[shortest].art; 
  
            if (waitingT[shortest] < 0) 
                waitingT[shortest] = 0; 
        } 
        t++; 
    }





    // printing table
    printf("\nProcess   A.T    B.T    Priority  C.T   T.T    W.T\n");
    for(int i=0; i<N; i++){
        printf("   P%d\t   %d\t   %d\t    %d\t   %d\t  %d\t %d\t\n", Tableess[i], arivalT[i], burstT[i], priority[i], completeT[i] ,turnaroundT[i], waitingT[i]);
    }


    // calculating average
    for(int i=0; i<N; i++){
        avgTT += turnaroundT[i];
        avgWT += waitingT[i];
    }
    printf("\nAverage Turnaround Time = %f\n", avgTT/N);
    printf("\nAverage Waiting Time = %f\n", avgWT/N);

    return 0;
}