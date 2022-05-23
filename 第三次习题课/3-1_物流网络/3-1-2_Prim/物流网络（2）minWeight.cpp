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

long long prim(){

    vector<bool> visited(n+1,false);
    vector<long long> minWeight(n+1,MAX_long);
    int cost = 0;
    minWeight[1] = 0;
    for(int iter = 1;iter<=n; iter++){
        int u = -1;
        for(int v = 1; v<=n; v++){
            if(!visited[v] && (u ==-1 || minWeight[u]>minWeight[v]))
                u = v;
        }
        cost +=minWeight[u];
        visited[u] = true;
        for(int i=0;i<adj[u].size();i++){
            int v = adj[u][i].first, weight = adj[u][i].second;
            if(!visited[v] && minWeight[v]>weight){
                minWeight[v] = weight;
            }
        }
    }
    return cost;
}

bool compare(const pair<int, long long> &a ,const pair<int, long long> &b){
    if (a.second == b.second){
        return a.first < b.second;
    }
    return a.second < b.second;
}
int main(){
    scanf("%d", &n);
    // 读取各个物流仓库的坐标 (x, y)
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &X[i], &Y[i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            adj[i].__emplace_back(make_pair(j,calc_cost(i,j)));
        }
        sort(adj[i].begin(),adj[i].end(),compare);
    }
    long long total_cost = prim();
    printf("%lld\n", total_cost);
    return 0;
}