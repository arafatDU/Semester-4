#include<bits/stdc++.h>
using namespace std;

#define N 5


void sortPriorityPair(vector<pair<int, int>> &pPair, int *burstT){
    for(int i=0; i<N; i++){
        for(int j=i; j<N; j++){
            pair<int, int> temp;
            
        }
    }
}

int main()
{
    int process[N] = {1, 2, 3, 4, 5};
    int arivalT[N] = {0, 0, 0, 0, 0};
    int burstT[N] = {2, 1, 8, 4, 5};
    int priority[N] = {2, 1, 4, 2, 3};

    int completeT[N], turnaroundT[N], waitingT[N], sum=0;
    float  avgTT=0, avgWT=0;
    vector< pair <int,int> > pPair;
    vector< pair <int,int> > cTpair;

    for(int i=0; i<N; i++){
        pPair.push_back( make_pair(priority[i], i ));
    }
    //sort(pPair.begin(), pPair.end());
    sortPriorityPair(pPair, burstT);


    for(int i=0; i<N; i++){
        sum += pPair[i].first;
        completeT[pPair[i].second] = sum;
        turnaroundT[pPair[i].second] = completeT[pPair[i].second] - arivalT[pPair[i].second];
        waitingT[pPair[i].second] = turnaroundT[pPair[i].second] - burstT[pPair[i].second];
    }




    for(int i=0; i<N; i++){
        cTpair.push_back( make_pair(completeT[i], i) );
    }
    sort(cTpair.begin(), cTpair.end());

    for(int i=0; i<N; i++) printf("|--- P%d ---|", cTpair[i].second+1);
    printf("\n0");
    for(int i=0; i<N; i++) printf("          %d", cTpair[i].first);
    printf("\n");


    printf("\nProcess   A.T    B.T    Priority  C.T   T.T    W.T\n");
    for(int i=0; i<N; i++){
        printf("   P%d\t   %d\t   %d\t    %d\t   %d\t  %d\t %d\t\n", process[i], arivalT[i], burstT[i], priority[i], completeT[i] ,turnaroundT[i], waitingT[i]);
    }


    for(int i=0; i<N; i++){
        avgTT += turnaroundT[i];
        avgWT += waitingT[i];
    }
    printf("\nAverage Turnaround Time = %f\n", avgTT/N);
    printf("\nAverage Waiting Time = %f\n", avgWT/N);

    return 0;
}