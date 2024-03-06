#include<bits/stdc++.h>
using namespace std;

#define N 5

int main()
{
    int process[N] = {1, 2, 3, 4, 5};
    int arivalT[N] = {0, 0, 0, 0, 0};
    int burstT[N] = {2, 1, 8, 4, 5};
    int priority[N] = {2, 1, 4, 2, 3};
    int quantum = 2;
    int time = 0;

    int completeT[N], turnaroundT[N], waitingT[N], sum=0;
    float  avgTT=0, avgWT=0;
    vector< pair <int,int> > aTpair;
    vector< pair <int,int> > cTpair;
    queue<int> pQueue;
    int remBurstT[N] = {2, 1, 8, 4, 5};
    

    for(int i=0; i<N; i++){
        aTpair.push_back( make_pair((arivalT[i]), i) );
    }
    sort(aTpair.begin(), aTpair.end());
    cout<<"-------------TEST---------------"<<endl;
    for(int i=0; i<N; i++) {
        pQueue.push(aTpair[i].second);
        cout<<"arrivalT: "<<aTpair[i].first<< "   index: "<<aTpair[i].second<<endl;
    }
    cout<<"-------------------------------\n\n"<<endl;





    while(!pQueue.empty()) {
       
            cout<<time;
            int p = pQueue.front();
            pQueue.pop();
            //cout<<"---front---"<<p<<endl;
            if(remBurstT[p] >= quantum){
                
                cout<<"___P"<<(p + 1)<<"___";

                
                time += quantum;
                remBurstT[p] -= quantum;
                
                if(remBurstT[p] > 0)
                    pQueue.push(p);
                else
                    completeT[p] = time;
            } else{
                
                cout<<"___P"<<(p + 1)<<"___";

                
                time += remBurstT[p];
                remBurstT[p] = 0;

                completeT[p] = time;
            }
            
        
    }
    cout<<time<<endl;
    



    for(int i=0; i<N; i++){
        turnaroundT[aTpair[i].second] = completeT[aTpair[i].second] - arivalT[aTpair[i].second];
        waitingT[aTpair[i].second] = turnaroundT[aTpair[i].second] - burstT[aTpair[i].second];
    }
    
    for(int i=0; i<N; i++){
        cTpair.push_back( make_pair(completeT[i], i) );
    }
    sort(cTpair.begin(), cTpair.end());



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