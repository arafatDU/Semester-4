#include <bits/stdc++.h>
using namespace std;

struct process
{
   int id;
   int burstTime;
   int priority;
   int arrivalTime;
   int completionTime;
   int remaining_burstTime;
   bool inqueue;
};

struct processDetails
{
   int id;
   int turnaroundTime;
   int waitingTime;
};

void priorityScheduling(vector<process> &processes);
bool compareByPriority(process &a, process &b);
void display(vector<process> &processes);
int getNextArrivalTime(vector<process> &processes, int currentTime);


int main()
{
   vector<process> processes = {
       {1, 20, 40, 5, 20, false, 0},
       {2, 25, 30, 20, 25, false, 0},
       {3, 25, 30, 30, 25, false, 0},
       {4, 15, 35, 10, 15, false, 0},
       {5, 10, 5, 100, 10, false, 0},
       {6, 10, 10, 105, 10, false, 0}};

   vector<processDetails> processInfo;
   double avgTurnaroundTime = 0.0, avgWaitingTime = 0.0;

   priorityScheduling(processes);

   for (int i = 0; i < processes.size(); i++)
   {
      int tt, wt;
      tt = processes[i].completionTime - processes[i].arrivalTime;
      wt = tt - processes[i].burstTime;

      processDetails pd;

      pd.id = processes[i].id;
      pd.turnaroundTime = tt;
      pd.waitingTime = wt;

      processInfo.push_back(pd);

      avgTurnaroundTime += tt;
      avgWaitingTime += wt;
   }

   cout << endl;

   for (int i = 0; i < processInfo.size(); i++)
      cout << processInfo[i].id << " " << processInfo[i].turnaroundTime << " " << processInfo[i].waitingTime << "\n";


   cout << "AvgTurnAround Time : " << avgTurnaroundTime / processes.size() << " AveWaitingTime: " << avgWaitingTime / processes.size()<<endl;
}



bool compareByPriority(process &a, process &b)
{
   return a.priority > b.priority;
}


void display(vector<process> &processes)
{
   for (int i = 0; i < processes.size(); i++)
      cout << processes[i].id << " " << processes[i].burstTime << " " << processes[i].priority << " " << processes[i].arrivalTime << "\n";
}

int getNextArrivalTime(vector<process> &processes, int currentTime)
{
   int next = -1;
   for (int i = 0; i < processes.size(); i++)
      if (processes[i].arrivalTime > next)
         next = processes[i].arrivalTime;


   for (int i = 0; i < processes.size(); i++)
      if (processes[i].arrivalTime < next && processes[i].arrivalTime > currentTime)
         next = processes[i].arrivalTime;

   return next;
}

void priorityScheduling(vector<process> &processes)
{
   int currentTime = 0,complete = 0, nextTime;
   vector<process> ready;

   cout << 0;
   while (complete < processes.size())
   {
      if (ready.size() != 0)
      {
         for (int i = 0; i < processes.size(); i++)
         {
            if (processes[i].arrivalTime <= currentTime && processes[i].inqueue == false)
            {
               ready.push_back(processes[i]);
               processes[i].inqueue = true;
            }
         }

         ready.push_back(ready[0]);
         ready.erase(ready.begin());
      }
      else
      {
         for (int i = 0; i < processes.size(); i++)
         {
            if (processes[i].arrivalTime <= currentTime && processes[i].inqueue == false)
            {
               ready.push_back(processes[i]);
               processes[i].inqueue = true;
            }
         }
      }

      if (ready.size() == 0)
      {
         nextTime = getNextArrivalTime(processes, currentTime);
         cout << "..." << nextTime;
         currentTime = nextTime;
      }

      else
      {
         sort(processes.begin(), processes.end(), compareByPriority);

         cout << "___P" << ready[0].id << "___";
         currentTime += ready[0].burstTime;
         for (int i = 0; i < processes.size(); i++)
         {
            if (ready[0].id == processes[i].id)
            {
               processes[i].completionTime = currentTime;
            }
         }
         complete++;
         ready.erase(ready.begin());
         cout << currentTime;
      }
   }
}