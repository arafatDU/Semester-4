#include<bits/stdc++.h>
using namespace std;

#define N 5


void sortPriorityPair(vector<pair<int, int>> &pPair, int *burstT){
    for(int i=0; i<N; i++){
        for(int j=i; j<N; j++){
            pair<int, int> temp;
            if(pPair[j].first > pPair[i].first){
                temp.first = pPair[j].first;
                temp.second = pPair[j].second;
                pPair[j].first = pPair[i].first;
                pPair[j].second = pPair[i].second;
                pPair[i].first = temp.first;
                pPair[i].second = temp.second;
            }else if(pPair[j].first == pPair[i].first){
                if(burstT[pPair[j].second] < burstT[pPair[i].second]){
                    temp.first = pPair[j].first;
                    temp.second = pPair[j].second;
                    pPair[j].first = pPair[i].first;
                    pPair[j].second = pPair[i].second;
                    pPair[i].first = temp.first;
                    pPair[i].second = temp.second;
                }
            }
            
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

    cout<<"-------------TEST---------------"<<endl;
    for(int i=0; i<N; i++) cout<<"priority: "<<pPair[i].first<< "   index: "<<pPair[i].second<<endl;
    cout<<"-------------------------------\n\n"<<endl;


    for(int i=0; i<N; i++){
        sum += arivalT[pPair[i].second] + burstT[pPair[i].second];
        completeT[pPair[i].second] = sum;
        turnaroundT[pPair[i].second] = completeT[pPair[i].second] - arivalT[pPair[i].second];
        waitingT[pPair[i].second] = turnaroundT[pPair[i].second] - burstT[pPair[i].second];
    }




    for(int i=0; i<N; i++){
        cTpair.push_back( make_pair(completeT[i], i) );
    }
    sort(cTpair.begin(), cTpair.end());

    // printing the Gnatt chart
    for(int i=0; i<N; i++) printf("|--- P%d ---|", cTpair[i].second+1);
    printf("\n0");
    for(int i=0; i<N; i++) printf("          %d", cTpair[i].first);
    printf("\n");


    // printing the table
    printf("\nProcess   A.T    B.T    Priority  C.T    T.T    W.T\n");
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