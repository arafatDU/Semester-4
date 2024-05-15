#include <bits/stdc++.h>

using namespace std;

struct process
{
    int id;
    int burstTime;
    int priority;
    int arrivalTime;
};

struct processDetails
{
   int id;
   int turnaroundTime;
   int waitingTime;
   int completionTime;
};

vector<int> test;

vector<processDetails> processInfo;

bool compareByArrivalTime(process &a, process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

bool compareByBurstTime(process &a, process &b)
{
    return a.burstTime < b.burstTime;
}

int nextArrivalTime(vector<process> &processes, int currentTime)
{
    int next = -1;

    for (int i = 0; i < processes.size(); i++)
    {
        if (processes[i].arrivalTime > next)
            next = processes[i].arrivalTime;
    }

    for (int i = 0; i < processes.size(); i++)
    {
        if (processes[i].arrivalTime < next and processes[i].arrivalTime > currentTime)
            next = processes[i].arrivalTime;
    }

    return next;
}

void display(vector<process> &processes)
{
   for (int i = 0; i < processes.size(); i++)
   {
      cout << processes[i].id << " " << processes[i].burstTime << " " << processes[i].priority << " " << processes[i].arrivalTime << " "<< "\n";
   }
}


void FCFS(vector<process> processes)
{
    int prefix = 0, i;
    sort(processes.begin(), processes.end(), compareByArrivalTime);

    // display(processes);
    cout << prefix;

    for (i = 0; i < processes.size() - 1; i++)
    {
        cout << "__P" << processes[i].id << "__";
        prefix += processes[i].burstTime;
        //test.push_back(prefix);
        processDetails p;

        p.id = processes[i].id;
        p.completionTime = prefix;

        processInfo.push_back(p);

        if (prefix < processes[i + 1].arrivalTime)
        {
            cout << prefix;
            cout << "...";
            prefix = processes[i + 1].arrivalTime;
        }
        cout << prefix;
         
    }

    if (prefix < processes[i].arrivalTime)
    {
        cout << prefix;
        cout << "...";
        prefix = processes[i + 1].arrivalTime;
    }
    else
    {
        cout << "__P" << processes[i].id << "__";
        prefix += processes[i].burstTime;
        processDetails p;

        p.id = processes[i].id;
        p.completionTime = prefix;

        processInfo.push_back(p);
        cout << prefix;
    }
}

int main()
{
    vector<process> processes = {
        {1, 20, 40, 0},
        {2, 25, 30, 25},
        {3, 25, 30, 30},
        {4, 15, 35, 60},
        {5, 10, 5, 100},
        {6, 10, 10, 105}
        };
    
     

   double avgTurnaroundTime = 0.0, avgWaitingTime = 0.0;

    FCFS(processes);

    cout << endl;

    // for(int i=0;i<processInfo.size();i++)
    // {
    //     cout << processInfo[i].id << " " << processInfo[i].completionTime << "\n";
    // }

   for (int i = 0; i < processes.size(); i++)
   {
      int tt, wt;
      tt = processInfo[i].completionTime - processes[i].arrivalTime;
      wt = tt - processes[i].burstTime;
      
      processInfo[i].turnaroundTime = tt;
      processInfo[i].waitingTime = wt;

      avgTurnaroundTime += tt;
      avgWaitingTime += wt;
   }

    cout << endl;

//     for (int i = 0; i < processInfo.size(); i++)
//    {
//       cout << processInfo[i].id << " " << processInfo[i].turnaroundTime << " " << processInfo[i].waitingTime << "\n";
//    }

   cout << "AvgTurnAround Time : " << avgTurnaroundTime / processes.size() << " AveWaitingTime: " << avgWaitingTime / processes.size();

    
}