#include<bits/stdc++.h>
using namespace std;

int p,r;


int main(){
    ifstream file("bankers.txt");
    file>>p>>r;

    int alloc[p][r],max_need[p][r],remaining_need[p][r],total[r],available[r];
    vector<int> seq;

    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            file>>alloc[i][j];
        }
    }
     for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            file>>max_need[i][j];
        }
    }

    for(int i=0;i<r;i++){
        file>>total[i];
    }

    // for(int i=0;i<r;i++) cout<<total[i]<<" ";

    file.close();	

      for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            remaining_need[i][j]=max_need[i][j]-alloc[i][j];
        }
    }

    for(int i=0;i<r;i++){
        int sum=0;
        for(int j=0;j<p;j++){

            sum+=alloc[j][i];
        }
        available[i]=total[i]-sum;
    }

    int count =0;
    int bool_seq[p]={0};

    for(int i=0;i<p;i++){
        for(int j=0;j<p;j++){
            int flag=0;
            for(int k=0;k<r;k++){
                if(remaining_need[j][k]>available[k]) flag=1;

            }
            if(flag==0 and bool_seq[j]==0){
                for(int k=0;k<r;k++){
                    available[k]+=alloc[j][k];
                }
                seq.push_back(j);
                // cout<<j<<" ";
                bool_seq[j]=1;

                // count++;
            }
        }
    }

    if(seq.size()!=p) cout<<"Deadlock\n";
    else{
        for(int i=0;i<p;i++) cout<<seq[i]+1<<" ";
    }
    cout<<endl;
}