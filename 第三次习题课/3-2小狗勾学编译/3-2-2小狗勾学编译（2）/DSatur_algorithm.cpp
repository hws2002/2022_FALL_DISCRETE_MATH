#include <iostream>
#include <set>
#include <tuple>
#include <vector>

using namespace std;
const int MAXN =15;
int n,m;

//================数据结构部分==========================
struct nodeInfo{
    int sat;// saturatin degree of the vertex
    int deg;// degree in the uncolourd subgraph
    int vertex;// Index of vertex
};

// Compares two nodes by saturation degree, then degree in the subgraph, then vertex label
struct maxSat{
    bool operator()(const nodeInfo& left, const nodeInfo& right) const {
        return tie(left.sat,left.deg,left.vertex) > tie(right.sat, right.deg, right.vertex);
    }
};

//graph representing an undirected graph
class Graph{
    int n;
    vector<int>  adj[MAXN+1];
    public :
        Graph(int numNodes){
            n = numNodes;
            // adj.resize(n, vector<int>());
        }
        // ~Graph() {adj.clear();}

        void addEdge(int u, int v);
        void DSatur();
};
//=================输入部分==================================
void Graph::addEdge(int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}
//==================求解部分===================================

void Graph::DSatur(){
    int u,i;
    // These are a (binary tree) priority queue, a set of colours adjacent to each uncoloured vertex (initially empty) 
    // and the degree d(v) of each uncoloured vertex in the graph induced by uncoloured vertices
    vector<bool> used(n+1,false);
    vector<int> c(n+1), d(n+1);
    vector<set<int> > adjCols(n+1);
    set<nodeInfo, maxSat> Q;
    set<nodeInfo, maxSat>::iterator maxPtr;
    set<int> colors; // to print the result
    for(u=0;u<=n;u++){
        c[u] = -1;
        d[u] = adj[u].size();
        adjCols[u] = set<int>();
        Q.emplace(nodeInfo{0,d[u],u});
    }
    while(!Q.empty()){
        maxPtr = Q.begin();
        u = (*maxPtr).vertex;
        Q.erase(maxPtr);
        for(int v : adj[u]){
            if (c[v] != -1) used[c[v]] = true;
        }

        for(i = 1;i<=n;i++){
            if (used[i] == false) break;
        }
        for(int v: adj[u]){
            if (c[v] != -1) used[c[v]] = false;
        }
        //Assign vertex u to color i
        c[u] = i;
        colors.insert(i);
        //Update the saturation degrees and degrees of all uncolored neighbours;
        //hence modify their corresponding elements in the priority queue
        for(int v: adj[u]){
            if (c[v] == -1){
                Q.erase({int(adjCols[v].size()),d[v],v});
                adjCols[v].insert(i); d[v]--;
                Q.emplace(nodeInfo{int(adjCols[v].size()),d[v],v});
            }
        }
    }
//===================输出部分===================================
    cout<<colors.size()<<endl;
    for(int u=1;u<=n;u++){
        cout<<c[u]<<" ";
    }
}

//====================main 函数===================================

int main(){
    scanf("%d %d",&n,&m);
    Graph G(n);
    int u,v;
    for(int i=0;i<m;i++){
        scanf("%d %d",&u,&v);
        G.addEdge(u,v);
    }
    G.DSatur();
    return 0;
}