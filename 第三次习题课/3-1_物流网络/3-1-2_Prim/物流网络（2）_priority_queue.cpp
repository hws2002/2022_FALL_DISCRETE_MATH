#include <iostream>
#include <vector>
#include <climits>
#include <cstdio>  // scanf, printf
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

const int MAX_N = 3000;
long long  MAX_long =  9223372036854775807;

int n;
int X[MAX_N+1], Y[MAX_N+1];

vector<pair<long long, int> > adj[MAX_N+1];


long long calc_cost(int i, int j) {
    long long res =  pow((abs(X[i] - X[j])),3) + pow((abs(Y[i] - Y[j])),3);
    return res;
}

bool compare(const pair<int, long long> &a ,const pair<int, long long> &b){
    if (a.second == b.second){
        return a.first < b.second;
    }
    return a.second < b.second;
}

#define PIL pair<long long, int>

priority_queue<PIL, vector<PIL>, greater<PIL> > dist;

void add_edge(int node){
    for(auto edge: adj[node]){
        dist.push(edge);
    }
}

long long prim(){
    long long cost = 0;
    vector<bool> selected(n+1,false);
    dist.push(PIL(0,1));
    for(int i=1;i<=n;i++){
        int now = -1; long long min_dist = MAX_long;
        while(!dist.empty()){
            now = dist.top().second;
            if(!selected[now]){
                min_dist = dist.top().first;
                break;
            }
            dist.pop();
        }
        //if(min_dist == MAX_long) return (long long );//연결 그래프가 아님
        cost += min_dist;
        selected[now] = true;
        add_edge(now);//사실 모든 node들끼리 연결되어있어서, add_edge보다는, modify_Edge가 더 나음 ,근데
        //priority_queue는 원소수정하려면 구현해야됨!
    }    
    return cost;
}

int main(){
    scanf("%d", &n);
    // 读取各个物流仓库的坐标 (x, y)D
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &X[i], &Y[i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            long long cost = calc_cost(i,j);
            adj[i].push_back(make_pair(cost,j));
            adj[j].push_back(make_pair(cost,i));
        }
    }
    long long total_cost = prim();
    printf("%lld\n", total_cost);
    return 0;
}