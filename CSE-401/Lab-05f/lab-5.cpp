#include <bits/stdc++.h>

using namespace std;

void FCFS(vector<int> &burstTime, vector<int> &priority)
{
    int time = 0, i;

    vector<int> turnaroundTime, waitingTime;

    for (i = 0; i < burstTime.size(); i++)
    {
        waitingTime.push_back(time);
        cout << time << "----";
        cout << "p" << i + 1 << "----";
        time += burstTime[i];
        turnaroundTime.push_back(time);
    }
    cout << time;

    // turnaround time

    double avgturnaroundTime = 0;

    cout << endl;
    for (i = 0; i < 5; i++)
    {
        avgturnaroundTime += turnaroundTime[i];
        cout << turnaroundTime[i] << " ";
    }

    cout << "\n"
         << avgturnaroundTime / burstTime.size();

    double avgwaitingTime = 0;

    cout << endl;
    for (i = 0; i < 5; i++)
    {
        avgwaitingTime += waitingTime[i];
        cout << waitingTime[i] << " ";
    }

    cout << "\n"
         << avgwaitingTime / burstTime.size();
}

void SJF(vector<int> &burstTime, vector<int> &priority)
{

    vector<pair<int, int>> process;

    vector<int> turnaroundTime, waitingTime;

    int i, time = 0;
    for (i = 0; i < burstTime.size(); i++)
    {
        int a, b;
        a = burstTime[i], b = i + 1;

        process.push_back({a, b});
    }

    sort(process.begin(), process.end());

    //  for(i=0;i<burstTime.size();i++)
    //   {

    //     cout << process[i].first << " " << process[i].second << "\n";
    //   }
    //   cout << "\n";

    for (i = 0; i < process.size(); i++)
    {
        waitingTime.push_back(time);
        cout << time << "----";
        cout << "p" << process[i].second << "----";
        time += process[i].first;
        turnaroundTime.push_back(time);
    }
    cout << time;

    double avgturnaroundTime = 0;

    cout << endl;
    for (i = 0; i < 5; i++)
    {
        avgturnaroundTime += turnaroundTime[i];
        // cout << turnaroundTime[i] << " ";
    }

    cout << "\n"
         << avgturnaroundTime / burstTime.size();

    double avgwaitingTime = 0;

    cout << endl;
    for (i = 0; i < 5; i++)
    {
        avgwaitingTime += waitingTime[i];
        // cout << waitingTime[i] << " ";
    }

    cout << "\n"
         << avgwaitingTime / burstTime.size();
}

void prioritySchedule(vector<int> &burstTime,vector<int> &priority)
{
    vector<pair<pair<int,int>,int>> process ;

    vector<int> turnaroundTime , waitingTime;

    int i , time = 0;
    for(i=0;i<burstTime.size();i++)
    {
       int a , b , c;
       a = burstTime[i] , b = i+1 , c = priority[i];

       process.push_back({{c,a},b});
    }

    sort(process.begin(),process.end());

    // for(i=0;i<burstTime.size();i++)
    // {

    //   cout << process[i].first.first << " " << process[i].first.second << " " << process[i].second<< "\n";
    // }
    // cout << "\n";

    for(i=0;i<process.size();i++)
   {
     waitingTime.push_back(time);
     cout << time << "----";
     cout << "p" << process[i].second << "----";
     time += process[i].first.second;
     turnaroundTime.push_back(time);
   }
   cout << time ;

   double avgturnaroundTime = 0;

   cout << endl;
   for(i=0;i<5;i++)
   {
     avgturnaroundTime += turnaroundTime[i];
     //cout << turnaroundTime[i] << " ";
   }

   cout << "\n" << avgturnaroundTime/burstTime.size();

   double avgwaitingTime = 0;

   cout << endl;
   for(i=0;i<5;i++)
   {
      avgwaitingTime += waitingTime[i];
     //cout << waitingTime[i] << " ";
   }

   cout << "\n" << avgwaitingTime/burstTime.size();
}

void RR(vector<int> &burstTime, vector<int> &priority)
{
    vector<int> ready_queue, change_burstTime , completion_time , waiting_time;
    int quantum = 2, value, prefix = 0 ;
    double avg_waiting_time = 0;

    for (int i = 0; i < burstTime.size(); i++)
    {
        ready_queue.push_back(i);
        change_burstTime.push_back(burstTime[i]);
        completion_time.push_back(0);
        waiting_time.push_back(0);
    }

    cout << "0";
    while (!ready_queue.empty())
    {
        int current_process = ready_queue.front();
        value = change_burstTime[current_process];

        if (value - quantum >= 0)
        {
            prefix += quantum;
            cout << "___P" << current_process + 1 << "___" << prefix;
            change_burstTime[current_process] -= quantum;
        }
        else
        {
            prefix += value;
            cout << "___P" << current_process + 1 << "___" << prefix;
            change_burstTime[current_process] = 0;
        }

        if (change_burstTime[current_process] == 0)
        {
            completion_time[current_process] = prefix;
            ready_queue.erase(ready_queue.begin());
        }
        else
        {
            ready_queue.push_back(current_process);
            ready_queue.erase(ready_queue.begin());
        }
     
    }

    cout << endl;
    //  for (int i=0;i<burstTime.size();i++)
    // {
    //     cout << completion_time[i] << " ";
    // }
     for (int i=0;i<burstTime.size();i++)
    {
        waiting_time[i] = completion_time[i] - burstTime[i];
    }

     for (int i=0;i<burstTime.size();i++)
    {
        waiting_time[i] = completion_time[i] - burstTime[i];
    }
    cout << endl;
    for (int i=0;i<burstTime.size();i++)
    {
        avg_waiting_time += waiting_time[i] ;
    }

    cout << avg_waiting_time/burstTime.size();

   
}

int main()
{

    vector<int> burstTime = {2, 1, 8, 4, 5};
    vector<int> priority = {2, 1, 4, 2, 3};

     cout << "First-Come, First-Served (FCFS):\n";
     FCFS(burstTime,priority);
     cout << endl;

     cout << "Shortest Job First(SJF):\n";
     SJF(burstTime,priority);

     prioritySchedule(burstTime,priority);

     RR(burstTime, priority);

    return 0;
}