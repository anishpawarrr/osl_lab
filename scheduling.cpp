#include<bits/stdc++.h>
using namespace std;

class process{
    public:
    int pid, at, wt, tat, bt, ct;
    process(int pidd, int att, int btt){
        pid = pidd;
        at = att;
        bt = btt;
        return;
    }
    void sjf(vector<process*>&p){
        int n = p.size();
        for(int i=0;i<n-1;i++){
            for(int j=0;j<n-i-1;j++){
                if(p[j]->bt > p[j+1]->bt){
                    swap(p[j],p[j+1]);
                }
            }
        }
        return;
    }
};



int main(){
    vector<process*>processes;
    int n;
    cout<<"Enter process no.\n";
    cin>>n;
    for(int i=0;i<n;i++){
        int at, bt;
        cout<<"at - > ";
        cin>>at;
        cout<<"bt -> ";
        cin>>bt;
        process *temp = new process(i+1, at, bt);
        processes.push_back(temp);
    }
    // vector<process*>queue;
    map<int, process*>mapp;
    map<int,bool>che;
    for(auto i:processes){
        mapp[i->at] = i;
        che[i->at] = 1;
    }
    int t = 0;
    vector<int>ch(100,0);
    // while(n){
    //     if(che[t]){
    //         queue.push_back(mapp[t]);
    //         che[t] = 0;
    //     }
    //     processes[0]->sjf(queue);
    //     if(queue.size()!=0){
    //         queue[0]->ct = t+queue[0]->bt;
    //         while(t<queue[0]->ct){
    //             ch[t] = queue[0]->pid;
    //             t++;
    //             if(che[t]){
    //                 queue.push_back(mapp[t]);
    //                 che[t] = 0;
    //             }
    //         }
    //         n--;
    //         swap(queue[0], queue[queue.size()-1]);
    //         queue.pop_back();
    //         t--;
    //     }
    //     t++;
        
    // }
    int ind = 0;
    int quantum = 1;
    queue<process*>q;
    while(n){
        if(che[t]){
            q.push(mapp[t]);
            che[t] = 0;
        }
        if(q.size()!=0){
            auto fr = q.front();
            q.pop();
            if(fr->bt > quantum){
                for(int i=0; i<quantum;i++){
                    ch[i+t] = fr->pid;
                    if(che[t+i]){
                        q.push(mapp[t+i]);
                        che[t] = 0;
                    }
                }
                fr->bt-=quantum;
                q.push(fr);
            }else{
                fr->ct = t-(fr->bt-quantum);
                for(int i=0;i<fr->bt;i++){
                    ch[i+t] = fr->pid;
                    if(che[t+i]){
                        q.push(mapp[t+i]);
                        che[t] = 0;
                    }
                }
                n--;
            }
        }
        t+=quantum;
        

    }

    for(auto i:ch){
        cout<<i;
    }
    cout<<endl;
    return 0;
}