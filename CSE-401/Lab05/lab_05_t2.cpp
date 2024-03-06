#include<bits/stdc++.h>
using namespace std;

#define N 6


void sortArrivalPair(vector<pair<int, int>> &aTpair, int *burstT){
    for(int i=0; i<N; i++){
        for(int j=i; j<N; j++){
            pair<int, int> temp;
            if(aTpair[j].first < aTpair[i].first){
                temp.first = aTpair[j].first;
                temp.second = aTpair[j].second;
                aTpair[j].first = aTpair[i].first;
                aTpair[j].second = aTpair[i].second;
                aTpair[i].first = temp.first;
                aTpair[i].second = temp.second;
            }else if(aTpair[j].first == aTpair[i].first){
                if(burstT[aTpair[j].second] < burstT[aTpair[i].second]){
                    temp.first = aTpair[j].first;
                    temp.second = aTpair[j].second;
                    aTpair[j].first = aTpair[i].first;
                    aTpair[j].second = aTpair[i].second;
                    aTpair[i].first = temp.first;
                    aTpair[i].second = temp.second;
                }
            }
            
        }
    }
}



int main()
{
    int process[N] = {1, 2, 3, 4, 5, 6};
    int arivalT[N] = {0, 25, 30, 60, 100, 105};
    int burstT[N] = {20, 25, 25, 15, 10, 10};
    int priority[N] = {40, 30, 30, 35, 5, 10};

    int completeT[N], turnaroundT[N], waitingT[N], sum=0;
    float  avgTT=0, avgWT=0;
    vector< pair <int,int> > aTpair;
    vector< pair <int,int> > cTpair;
    

    for(int i=0; i<N; i++){
        aTpair.push_back( make_pair((arivalT[i]), i) );
    }
    sortArrivalPair(aTpair, burstT);
    cout<<"-------------TEST---------------"<<endl;
    for(int i=0; i<N; i++) cout<<"arrivalT: "<<aTpair[i].first<< "   index: "<<aTpair[i].second<<endl;
    cout<<"-------------------------------\n\n"<<endl;


    for(int i=0; i<N; i++){
        sum += burstT[aTpair[i].second];
        completeT[aTpair[i].second] = sum;
        turnaroundT[aTpair[i].second] = completeT[aTpair[i].second] - arivalT[aTpair[i].second];
        waitingT[aTpair[i].second] = turnaroundT[aTpair[i].second] - burstT[aTpair[i].second];
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