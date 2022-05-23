#include <iostream>
#include <climits>
#include <vector>

using namespace std;
int n,L;
int Distance[20][20] = {0};
int Cost[20][20] = {0};
int path[20] = {0};
bool visited[20] = {false};
int s_dis = INT_MAX;
int cost = 0;
int dist = 0;
int c_path[20] = {0};

void updateSolution(){
    if(dist < s_dis){
        for(int i=1;i<=n;i++){
            c_path[i] = path[i];
        }
        s_dis = dist;
        return;
    } else{//dist == s_dis
        for(int i=1;i<=n;i++){
            if(c_path[i]==path[i]){
                continue;
            } else if(c_path[i]<path[i]){
                return;
            } else{
                for(int j=1;j<=n;j++){
                    c_path[j] = path[j];
                }
                return;
            }
        s_dis = dist; 
        }
    }
}

void search(int m){
    if (cost>L) {
        return;
    }
    if(dist > s_dis){
        return;
    }
    if(m == n+1){//이미 거리,비용 검증됨
        
        updateSolution();
        return;
    }
    for(int i=1;i<=n;i++){
        if(visited[i]) continue;
        visited[i] = true;
        path[m] = i;
        int c_add = Cost[path[m-1]][i];
        int d_add = Distance[path[m-1]][i];
        cost += c_add;
        dist += d_add;
        search(m+1);
        cost -= c_add;
        dist -= d_add;
        visited[i] = false;
    }
    return;
}


int main(){
    cin>>n>>L;
    //输入城市间道路长度
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>Distance[i][j];
        }
    }
    //交通费用
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>Cost[i][j];
        }
    }
    search(1);
    if(c_path[1] ==0){
        cout<<-1;
        return 0;
    }
    cout<<s_dis<<endl;
    for(int i=1;i<=n;i++){
        cout<<c_path[i]<<" ";
    }
    return 0;
}
