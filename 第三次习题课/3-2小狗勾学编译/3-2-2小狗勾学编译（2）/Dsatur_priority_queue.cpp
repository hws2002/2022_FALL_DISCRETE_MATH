#include <iostream>
#include <set>
#include <tuple>
#include <vector>
#include <list>
#include <queue>
#define TIII tuple<int, int, int>

using namespace std;
//================数据结构部分==========================
const int MAXN =15;
int n,m;
vector<int> adj[MAXN+1];

// Compares two nodes by saturation degree, then degree in the subgraph, then vertex label
struct myComparator
{ 
    bool operator()(TIII & left, TIII & right)
    {
    // if(get<0>(left) != get<0>(right)) return get<0>(left) > get<0>(right);
    // if(get<1>(left) != get<1>(right)) return get<1>(left) > get<1>(right);
    // return get<2> (left) > get<2>(right);
    return tie(get<0>(left),get<1>(left),get<2>(left)) < tie(get<0>(right), get<1>(right), get<2>(right));
    }
};

template<typename T, class Container=std::vector<T>, class Compare=std::less<typename Container::value_type> >
class custom_priority_queue : public std::priority_queue<T, Container, Compare>
{
  public:

      bool remove(const T& value) {
        auto it = std::find(this->c.begin(), this->c.end(), value);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
       }
       else {
        return false;
       }
 }
};
custom_priority_queue< TIII, vector<TIII> , myComparator > Queue;


//=================输入部分==================================
void addEdge(int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}
void input(){
    scanf("%d %d",&n,&m);
    int u,v;
    for(int i=0;i<m;i++){
        scanf("%d %d",&u,&v);
        addEdge(u,v);
    }
}

//==================求解部分===================================
set<int> colors;
int color_assigned[MAXN+1] = {0};

void DSatur(){
    // These are a (binary tree) priority queue, a set of colours adjacent to each uncoloured vertex (initially empty) 
    // and the degree d(v) of each uncoloured vertex in the graph induced by uncoloured vertices
    int degree[MAXN+1] = {0};   
    vector<int> adjacent_color[MAXN+1];
    for(int u=1;u<=n;u++){
        adjacent_color[u].clear();
        degree[u] = adj[u].size();
        Queue.push(make_tuple(0,adj[u].size(),u));
    }
    while(!Queue.empty()){
        vector<bool> color_canassign(n+1,true);
        int u = get<2>(Queue.top());
        Queue.pop();
        for(int v : adj[u]){
            if (color_assigned[v] != 0) color_canassign[color_assigned[v]] = false;
        }

        for(int i = 1; i<=n;i++){
            if (color_canassign[i] == true) {
                //Assign vertex u to color i
                color_assigned[u] = i;
                break;
            }
        }
        colors.insert(color_assigned[u]);
        //Update the saturation degrees and degrees of all uncolored neighbours;
        //hence modify their corresponding elements in the priority queue
        for(int v: adj[u]){
            if(color_assigned[v] == 0){// haven't assigend color yet
                Queue.remove({int(adjacent_color[v].size()),degree[v],v});
                adjacent_color[v].push_back(u);degree[v] -= 1;
                Queue.push({int(adjacent_color[v].size()),degree[v],v});
            }
        }
    }
}

//===================输出部分===================================
void print_chromatic_number(){
        cout<<colors.size()<<endl;
        for(int u=1;u<=n;u++){
            cout<<color_assigned[u]<<" ";
        }
}

//====================main 函数===================================

int main(){
    input();
    DSatur();
    print_chromatic_number();
    return 0;
}