#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
//enQueue,deQueue이런식으로 구현하면, front, rear 가 계속 증가할수밖에없음,
//그러면 Segmentation Fault가 생길수도!
//items은 capacity가 n인데, front, rear가 n보다 커질 수 있다는 얘기!
//충분히 발생할 수 있는 이유 : 重边，自环을 포함하니까!

void BFS(int s,vector<int>* g, bool* visited){
    //储存工作结点的queue
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        cout<<u<<" ";
        for(int i=g[u].size()-1;i>=0;i--){
            if(visited[g[u][i]] == false){
                q.push(g[u][i]);
                visited[g[u][i]] = true;
            }
        }
    }
}

//递归
void DFS(int s,vector<int>* g,bool* visited){
    if(visited[s]) return;
    visited[s] = 1;
    cout<<s<<" ";
    for(int i=g[s].size()-1;i>=0;i--){
        int next = g[s][i];
        DFS(next,g,visited);
    }
}


int main(){
    int n,m,s = 0;
    cin>>n>>m>>s;// n, m, s，表示图的 结点数、图的 边数、搜索的开始结点。
    vector<int> *graph = new vector<int>[n+1];
    bool visited[n+1];
    fill(visited,visited+n+1,false);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;//u,v <=n
        graph[u].push_back(v);
    }
    BFS(s,graph,visited);
    cout<<endl;

    fill(visited,visited+n+1,false);
    DFS(s,graph,visited);
    delete [] graph;
    return 0;
}
/*
1 ≤ n ≤ 200000, 1 ≤ m ≤ 1000000

1 ≤ s ≤ n

1 ≤ u, v ≤ n

注意：图 G 中可能存在重边和自环

时间限制：1 秒

内存限制：256 MiB
*/