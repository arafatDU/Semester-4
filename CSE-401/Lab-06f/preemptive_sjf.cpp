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
      cout << processes[i].id << " " << processes[i].burstTime << " " << processes[i].priority << " " << processes[i].arrivalTime << " " << processes[i].completionTime << "\n";
   }
}

bool compareByRemainingBurstTime(process &a, process &b)
{
   return a.remaining_burstTime < b.remaining_burstTime;
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

void SJF(vector<process> &processes)
{
   int complete = 0, currentTime = 0, nextTime;

   vector<process> ready;

   cout << 0;
   while (complete < processes.size())
   {
      for (int i = 0; i < processes.size(); i++)
      {
         if (processes[i].arrivalTime <= currentTime and processes[i].inqueue == false)
         {
            ready.push_back(processes[i]);
            processes[i].inqueue = true;
         }
      }
      sort(ready.begin(), ready.end(), compareByRemainingBurstTime);

      while (ready[0].remaining_burstTime)
      {
         ready[0].remaining_burstTime--;
         currentTime++;

         for (int i = 0; i < processes.size(); i++)
         {
            if (processes[i].arrivalTime <= currentTime and processes[i].inqueue == false)
            {
               if (processes[i].remaining_burstTime < ready[0].remaining_burstTime)
               {
                  cout << "___P" << ready[0].id << "___" << currentTime;
                  ready.insert(ready.begin(), processes[i]);
                  processes[i].inqueue = true;
               }
            }
         }
      }

      cout << "___P" << ready[0].id << "___" << currentTime;
          for(int i=0;i<processes.size();i++)
         {
            if(ready[0].id == processes[i].id)
            {
               processes[i].completionTime = currentTime;
            }
         }
      ready.erase(ready.begin());
      complete++;

      if (ready.size() == 0 and complete < processes.size())
      {
         nextTime = nextArrivalTime(processes, currentTime);

         if (currentTime < nextTime)
         {
            cout << "..." << nextTime;
            currentTime = nextTime;
         }
      }
   }

}

int main()
{
   vector<process> processes = {
       {1, 20, 40, 0, 20, false, 0},
       {2, 25, 30, 25, 25, false, 0},
       {3, 25, 30, 30, 25, false, 0},
       {4, 15, 35, 60, 15, false, 0},
       {5, 10, 5, 100, 10, false, 0},
       {6, 10, 10, 105, 10, false, 0}};
  

   vector<processDetails> processInfo;

   double avgTurnaroundTime = 0.0, avgWaitingTime = 0.0;

   SJF(processes);

    for(int i=0;i<processes.size();i++)
    {
       int tt , wt;
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

   cout << "AvgTurnAround Time : " << avgTurnaroundTime/processes.size() << " AveWaitingTime: " << avgWaitingTime/processes.size() << endl;
}