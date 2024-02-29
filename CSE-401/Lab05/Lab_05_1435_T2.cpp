#include<bits/stdc++.h>
using namespace std;

#define N 5

int main()
{
    int process[N] = {1, 2, 3, 4, 5};
    int arivalT[N] = {0, 0, 0, 0, 0};
    int burstT[N] = {2, 1, 8, 4, 5};
    int priority[N] = {2, 1, 4, 2, 3};

    int completeT[N], turnaroundT[N], waitingT[N], sum=0;
    float  avgTT=0, avgWT=0;
    vector< pair <int,int> > bTpair;
    vector< pair <int,int> > cTpair;
    

    for(int i=0; i<N; i++){
        bTpair.push_back( make_pair((arivalT[i]+ burstT[i]), i) );
    }
    sort(bTpair.begin(), bTpair.end());
    cout<<"-------------TEST---------------"<<endl;
    for(int i=0; i<N; i++) cout<<"burstT: "<<bTpair[i].first<< "   index: "<<bTpair[i].second<<endl;
    cout<<"-------------------------------\n\n"<<endl;


    for(int i=0; i<N; i++){
        sum += bTpair[i].first;
        completeT[bTpair[i].second] = sum;
        turnaroundT[bTpair[i].second] = completeT[bTpair[i].second] - arivalT[bTpair[i].second];
        waitingT[bTpair[i].second] = turnaroundT[bTpair[i].second] - burstT[bTpair[i].second];
    }




    for(int i=0; i<N; i++){
        cTpair.push_back( make_pair(completeT[i], i) );
    }
    sort(cTpair.begin(), cTpair.end());

    // printing Gantt chart
    for(int i=0; i<N; i++) printf("|--- P%d ---|", cTpair[i].second+1);
    printf("\n0");
    for(int i=0; i<N; i++) printf("          %d", cTpair[i].first);
    printf("\n");


    // printing table
    printf("\nProcess   A.T    B.T    Priority  C.T   T.T    W.T\n");
    for(int i=0; i<N; i++){
        printf("   P%d\t   %d\t   %d\t    %d\t   %d\t  %d\t %d\t\n", process[i], arivalT[i], burstT[i], priority[i], completeT[i] ,turnaroundT[i], waitingT[i]);
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