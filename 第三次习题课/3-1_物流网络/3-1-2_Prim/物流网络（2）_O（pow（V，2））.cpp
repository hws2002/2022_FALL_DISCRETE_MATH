#include <iostream>
#include <vector>
#include <climits>
#include <cstdio>  // scanf, printf
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX_N = 3000;
long long  MAX_long =  9223372036854775806;

int n;
int X[MAX_N+1], Y[MAX_N+1];

vector<pair<int, long long> > adj[MAX_N+1];


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

long long prim(){
    long long cost = 0;
    vector<bool> selected(n+1,false);
    vector<long long> dist(n+1,MAX_long);
    dist[1] = 0;
    for(int i=1;i<=n;i++){
        int now = -1;
        long long min_dist = MAX_long;
        for(int j=1;j<=n;j++){
            if(!selected[j] && min_dist > dist[j]){
                min_dist = dist[j];
                now = j;
            }
        }
        cost += min_dist;
        selected[now] = true;
        for(auto edge : adj[now])
            dist[edge.first] = min(dist[edge.first],edge.second);
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
        for(int j=1;j<=n;j++){
            adj[i].push_back(make_pair(j,calc_cost(i,j)));
        }
    }
    
    long long total_cost = prim();
    printf("%lld\n", total_cost);
    return 0;
}