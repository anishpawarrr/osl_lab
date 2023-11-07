#include<bits/stdc++.h>
using namespace std;

int insert_fifo(vector<int>&frames, queue<int>&q, int frame_size, int page){
    if(frames.size()<frame_size){
        frames.push_back(page);
        q.push(page);
        return 0;
    }
    for(int i:frames){
        if(i == page)return 1;
    }
    int pop = q.front();
    q.pop();
    for(int i = 0; i<frame_size; i++){
        if(frames[i] == pop){
            frames[i] = page;
            q.push(page);
            return 0;
        }
    }
    return -1;
}

int insert_lru(vector<vector<int>>&frames, int frame_size, int page, int &time){
    if(frames.size()<frame_size){
        frames.push_back({page,++time});
        return 0;
    }
    for(int i=0; i<frame_size; i++){
        if(frames[i][0] == page){
            frames[i][1] = ++time;
            return 1;
        }
    }
    int recent = INT_MAX;
    int replace;
    for(int i=0; i<frame_size; i++){
        if(recent > frames[i][1]){
            recent = frames[i][1];
            replace = i;
        }
    }
    frames[replace] = {page, ++time};
    return 0;
}

int insert_optimal(vector<int>&pages, vector<int>&frames, int frame_size, int page_ind){
    if(frames.size()<frame_size){
        frames.push_back(pages[page_ind]);
        return 0;
    }
    for(int i=0;i<frame_size;i++){
        if(pages[page_ind] == frames[i])return 1;
    }
    vector<int>future_occurence(frame_size, INT_MAX);
    for(int i=0;i<frame_size;i++){
        for(int j = page_ind; j<pages.size();j++){
            if(pages[j] == frames[i]){
                future_occurence[i] = j;
            }
        }
    }
    int replace, most_ahead = INT_MIN;
    for(int i=0; i<frame_size; i++){
        if(most_ahead < future_occurence[i]){
            replace = i;
            most_ahead = future_occurence[i];
        }
    }
    frames[replace] = pages[page_ind];
    return 0;
}

void print_frame(vector<int>frame){
    cout<<endl;
    for(int i:frame){
        cout<<i<<" ";
    }
    cout<<endl;
}

void print_frame_lru(vector<vector<int>>&frames){
    for(auto i:frames){
        cout<<i[0]<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int>frame;
    queue<int>que;
    int frame_size = 3;
    vector<int>pages = {1,2,3,2,3,4,6,5,1,4};
    vector<vector<int>>lru_frame;
    int time = 0;
    for(int i=0; i<pages.size();i++){
        int res = insert_optimal(pages, frame, frame_size, i);
        if(res){
            cout<<"Hit";
        }else{
            cout<<"Miss";
        }
        print_frame(frame);
        cout<<endl;
    }
    return 0;
}