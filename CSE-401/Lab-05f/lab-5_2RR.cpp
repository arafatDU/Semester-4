#include <bits/stdc++.h>

using namespace std;

struct process
{
   int id;
   int burstTime;
   int priority;
   int arrivalTime;
   int remaining_burstTime;
   bool inqueue;
   int completionTime;
};

struct processDetails
{
   int id;
   int turnaroundTime;
   int waitingTime;
};

void display(vector<process> &processes)
{
   for (int i = 0; i < processes.size(); i++)
   {
      cout << processes[i].id << " " << processes[i].burstTime << " " << processes[i].priority << " " << processes[i].arrivalTime << "\n";
   }
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

void RR(vector<process> &processes)
{
   int complete = 0, currentTime = 0, quantum = 5, nextTime;

   vector<process> ready;

   cout << 0;
   while (complete < processes.size())
   {
      if (ready.size() != 0)
      {
         for (int i = 0; i < processes.size(); i++)
         {
            if (processes[i].arrivalTime <= currentTime and processes[i].inqueue == false)
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
            if (processes[i].arrivalTime <= currentTime and processes[i].inqueue == false)
            {
               ready.push_back(processes[i]);
               processes[i].inqueue = true;
            }
         }
      }

      if (ready.size() == 0)
      {
         nextTime = nextArrivalTime(processes, currentTime);
         cout << "..." << nextTime;
         currentTime = nextTime;
      }

      else
      {
         cout << "___P" << ready[0].id << "___";

         if (ready[0].remaining_burstTime <= quantum and ready[0].remaining_burstTime > 0)
         {
            currentTime += ready[0].remaining_burstTime;
            ready[0].remaining_burstTime = 0;
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
         else
         {
            ready[0].remaining_burstTime -= quantum;
            currentTime += quantum;
            cout << currentTime;
         }
      }
   }
}

int main()
{
   vector<process> processes = {
       {1, 20, 40, 0, 20, false, 0},
       {2, 25, 30, 25, 25, false,0},
       {3, 25, 30, 30, 25, false,0},
       {4, 15, 35, 60, 15, false,0},
       {5, 10, 5, 100, 10, false,0},
       {6, 10, 10, 105, 10, false,0}};

       vector<processDetails> processInfo;

   double avgTurnaroundTime = 0.0, avgWaitingTime = 0.0;

   RR(processes);

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

   //  for (int i = 0; i < processInfo.size(); i++)
   // {
   //    cout << processInfo[i].id << " " << processInfo[i].turnaroundTime << " " << processInfo[i].waitingTime << "\n";
   // }

   cout <<endl<< "AvgTurnAround Time : " << avgTurnaroundTime / processes.size() << " AveWaitingTime: " << avgWaitingTime / processes.size()<<endl;

   
}