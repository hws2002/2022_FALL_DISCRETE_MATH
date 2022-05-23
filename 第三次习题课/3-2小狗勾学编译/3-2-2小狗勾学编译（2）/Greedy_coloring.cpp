#include <stdio.h>
#include <vector>
using namespace std;

const int MAXN = 15;
void add_color(int u, int cr);
//============================================================
// 数据结构部分
int n,m;

std::vector<int> adj[MAXN+1];

//===========================================================
// 输入部分
void add_Edge(int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void input(){
    scanf("%d %d",&n,&m);
    int u,v;
    for(int i=0;i<m;i++){
        scanf("%d %d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

//=============================================================
// 求解部分

vector<int> colored(MAXN+1,0);
int cr;//最后用于输出答案

void chromatic_number(){
    colored[1] = 1;//1번노드에 1번색깔 입히기
    for(int u = 2;u<=n;u++){
        vector<int>::iterator v;
        vector<bool> color(MAXN+1,true);
        for(v = adj[u].begin();v!= adj[u].end();v++){
            if(colored[*v] != 0){
                color[colored[*v]] = false;
            }
        }
        for(cr = 1; cr <=n; cr++){
            if(color[cr] == true) break;
        }
        colored[u] = cr;
    }
}

//========================================================
// 输出部分

void print_result(){
    printf("%d\n", cr);
    for(int i=1;i<=n;i++){
        printf("%d ",colored[i]);
    }
}

//===================================================
// main 函数

int main(){
    input();
    chromatic_number();
    print_result();
    return 0;
}