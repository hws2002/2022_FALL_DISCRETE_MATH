#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 0x3fffffff;
const int MAXN = 40;

int inline min(int a, int b) { return a < b ? a : b; }

//
// 记录结点标号（结点编号从 1 开始）
// direction[u] = 1 表示标号为正，-1 表示标号为负，0 表示未标号
// from[u] 表示结点 u 是因为哪个结点才得到标号的
// delta[u] 表示从源到 u 的增流路径上最大的可增流量
//
int direction[MAXN + 1], from[MAXN + 1], delta[MAXN + 1];
int max_flow = 0;
int n, m, s, t;

vector<int> flow;

class Graph {
public:
    // TODO: 选择适合本题的图数据结构并实现
    pair<int, int> edge[MAXN+1][MAXN+1];
    vector< int > adj[MAXN+1];
    vector< int > adj_[MAXN+1]; 
    // 返回指定边的流量
    int Flow(int u, int v) { 
        return edge[u][v].second; 
    }
    // 返回指定边的容量
    int Capacity(/*TODO*/int u, int v) { 
        return edge[u][v].first;
    }
    // 添加一条从 u 到 v 的单向边，容量为 c，流量为 f
    void AddEdge(int u, int v, int c, int f) {
        /* TODO */
        edge[u][v] = make_pair(c,f);
        adj[u].push_back(v);
        adj_[v].push_back(u);
    }
} G;

//
// 适用于 Edmonds-Karp 算法的标号过程，基于广度优先搜索给所有结点标号
//
void label_bfs() {
    static int q[MAXN + 1];
    int hd = 0, tl = 0;
    q[tl++] = s; // 第一个搜索源点
    while (hd < tl) {
        int u = q[hd++]; // 按入队顺序取出未标号结点
        vector<int>::iterator ptr;
        for (ptr = G.adj[u].begin();ptr!=G.adj[u].end();ptr++/* TODO: 枚举每一个 v 满足 (u, v) 在图中 */) {
            int v = *ptr;
            // 如果 v 访问过，跳过该结点
            if (direction[v] != 0)
                continue;
            int c = G.Capacity(u,v);
            int f = G.Flow(u,v);
            if (/* TODO: 判断是否需要更新 v 的标号 */c>f) {
                // TODO: 更新标号
                direction[v] = 1;
                from[v] = u;
                delta[v] = min(delta[u], c-f);
                q[tl++] = v; // 从 v 出发，搜索邻接的未标号结点
            }
        }
        for (ptr = G.adj_[u].begin();ptr!=G.adj_[u].end();ptr++/* TODO: 枚举每一个 v 满足 (v, u) 在图中 */) {
            int v = *ptr;
            if(direction[v] != 0) continue;
            int c = G.Capacity(v,u);
            int f = G.Flow(v,u);
            if(f>0){
                direction[v] = -1;
                from[v] = u;
                delta[v] = min(delta[u],f);
                q[tl++] = v;
            }
        }
    }
}            
//
bool label() {
    // TODO: 初始化标号数组
    for(int i=1;i<=n;i++){
        direction[i] = 0;
        from[i] = -1;
        delta[i] = INF;
    }
    direction[s] = -1;
    // 深度/广度优先搜索的调用入口，基于 bfs 或 dfs 实现均可
    label_bfs();//Edmons-Karp
    // 通过汇点是否被标号判断允许流是否存在
    return direction[t] != 0;
}

void printPath() {
    int pathLength = 0;
    static int Path[MAXN + 1];
    // 根据记录的 from 数组，从汇点倒推出增流路径
    for (int v = t; v != s; v = from[v]) {
        Path[pathLength++] = v;
    }
    // TODO: 按照题目要求向标准输出中打印结果
    printf("%d %d\n",pathLength+1,delta[t]);
    printf("%d ",s);
    for(int i=pathLength-1;i>=0;i--){
        printf("%d ",Path[i]);
    }
}

void init() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 0; i < m; i++) {
        int u, v, c, f;
        scanf("%d%d%d%d", &u, &v, &c, &f);
        G.AddEdge(u, v, c, f);
    }
}

int main() {
    init();
    if (label()) {
        printPath();
    } else {
        printf("-1\n");
    }
}