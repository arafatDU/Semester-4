#include <iostream>
#include <algorithm> 
#include <iomanip> 
using namespace std;


#define N 6

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrival(process p1, process p2) 
{ 
    return p1.arrival_time < p2.arrival_time;
}

bool compareID(process p1, process p2) 
{  
    return p1.pid < p2.pid;
}

int main() {

    int pid[N] = {1, 2, 3, 4, 5, 6};
    int arivalT[N] = {0, 25, 30, 60, 100, 105};
    int burstT[N] = {20, 25, 25, 15, 10, 10};
    int priority[N] = {40, 30, 30, 35, 5, 10};
    
    struct process p[N];
    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    //cout << setprecision(2) << fixed;


    for(int i = 0; i < N; i++) {
        p[i].pid = pid[i];
        p[i].arrival_time = arivalT[i];
        p[i].burst_time = burstT[i];
    }

    sort(p,p+N,compareArrival);

    for(int i = 0; i < N; i++) {
        p[i].start_time = (i == 0)?p[i].arrival_time:max(p[i-1].completion_time,p[i].arrival_time);
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
    }

    avg_turnaround_time = (float) total_turnaround_time / N;
    avg_waiting_time = (float) total_waiting_time / N;
    
    //sort(p,p+N,compareID);
    cout<<"Gantt chart: "<<endl;
    for(int i=0; i<N; i++){
      cout<<p[i].start_time<<"---P"<<p[i].pid<<"---"<<p[i].completion_time;
      if(i != N-1) cout<<"----";
    }

    cout<<endl<<endl;
    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

    for(int i = 0; i < N; i++) {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<"\n"<<endl;
    }
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;


}

/*

AT - Arrival Time of the process
BT - Burst time of the process
ST - Start time of the process
CT - Completion time of the process
TAT - Turnaround time of the process
WT - Waiting time of the process
RT - Response time of the process

Formulas used:

TAT = CT - AT
WT = TAT - BT
RT = ST - AT

*/