#include<bits/stdc++.h>
using namespace std;

int main(){
    freopen("bankers_input2.txt", "r", stdin);
    int numProcess, numResource;
    cin >> numProcess >> numResource;
    vector<vector<int>> allocation, maxx, need;
    allocation.resize(numProcess, vector<int>(numResource));
    maxx.resize(numProcess, vector<int>(numResource));
    need.resize(numProcess, vector<int>(numResource));
    vector<int> available(numResource);
    for(int i = 0; i < numProcess; i++){
        for(int j = 0; j < numResource; j++){
            cin >> allocation[i][j];
        }
    }
    for(int i = 0; i < numProcess; i++){
        for(int j = 0; j < numResource; j++){
            cin >> maxx[i][j];
        }
    }
    for(int i = 0; i < numResource; i++){
        cin >> available[i];
    }
    for(int i = 0; i < numProcess; i++){
        for(int j = 0; j < numResource; j++){
            need[i][j] = maxx[i][j] - allocation[i][j];
        }
    }
    vector<int> work(numResource);
    work = available;
    vector<bool> finish(numProcess, false);
    int initNumFinish = 0, numFinish = 0;
    int requestedProcess;
    vector<int> requestedResource(numResource);
    cin>>requestedProcess;
    for(int i = 0; i < numResource; i++){
        cin >> requestedResource[i];
    }
    vector<string> order;
    bool isPossible = true;
    for(int i = 0; i < numProcess; i++){
        if(requestedResource[i] > available[i]){
            isPossible = false;
            break;
        }
    }
    if(isPossible){
        finish[requestedProcess] = true;
        for(int i = 0; i < numResource; i++){
            allocation[requestedProcess][i] += requestedResource[i];
            need[requestedProcess][i] -= requestedResource[i];
            work[i] -= requestedResource[i];
            if(need[requestedProcess][i] != 0){
                finish[requestedProcess] = false;
            }
        }
        if(finish[requestedProcess]){
            numFinish++;
            order.push_back("P" + to_string(requestedProcess));
            initNumFinish = numFinish;
        }
        
    }
    // cout << "Allocation:" << endl;
    // for(auto r : allocation){
    //     for(auto c : r){
    //         cout << c << " ";
    //     }
    //     cout << endl;
    // }
    //     cout << endl;
    // cout << "Maximum:" << endl;
    // for(auto r : maxx){
    //     for(auto c : r){
    //         cout << c << " ";
    //     }
    //     cout << endl;
    // }
    //     cout << endl;
    // cout << "Need:" << endl;
    // for(auto r : need){
    //     for(auto c : r){
    //         cout << c << " ";
    //     }
    //     cout << endl;
    // }
    // for(auto a : available){
    //     cout << a << " ";
    // }
    //     cout << endl;
    //     cout << endl;
    while(true){
        for(int i = 0; i < numProcess; i++){
            if(!finish[i]){
                isPossible = true;
                for(int j = 0; j < numResource; j++){
                    if(need[i][j] > work[j]){
                        isPossible = false;
                        break;
                    }
                }
                if(isPossible){
                    for(int j = 0; j < numResource; j++){
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    numFinish++;
                    order.push_back("P" + to_string(i));
                }
            }
        }
        if(initNumFinish == numFinish) break;
        else initNumFinish = numFinish;
    }
    bool isSafe = true;
    for(auto fin : finish){
        if(!fin){
            cout << "System is unsafe" << endl;
            isSafe = false;
            break;
        }
    }
    if(isSafe){
        cout << "System is safe" << endl;
        cout << "Allocation order is: ";
        for(auto o: order){
            cout << o << " ";
        }
        cout << endl << endl;
    }
}