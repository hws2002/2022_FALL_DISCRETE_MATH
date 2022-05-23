#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int map[20][20]={0};
int cost[20][20] = {0};
vector<pair<int,int> > graph;
vector<pair<int,int> > route;
vector<vector<int> > c_route;
vector<int>::iterator iter;
vector<int> indices;
int n,L;
int s_dis = INT_MAX;
int edge = 0;
int n_distance = 0;
int n_cost = 0;
int &edge_p = edge;
int &distance_p = n_distance;
int &cost_p = n_cost;
bool visited_d[19]={false};//之前从这个城市出发过
bool visited_a[19]={false};//之前把这个城市设为目的地

/*제약조건들
1. 是否访问过-> visited
2. 访问该城市是否超过s_dis（shortest distance)
3. 是否超过cost 限制
DFS실행방식
graph는 가는 경로를 최단으로했을때를 기준으로 sort해놓은 벡터다!
즉, index를 하나씩 늘려가면서, 위 제약조건에 맞는지 확인한다, 그럼으로써 route들을 하나씩 구하고,그 루트들을 c_route에다가 추가하는식으로!
c_route는 갈수있는 최단경로들을 모아둔것!
*/



int find_from(int to_find,int arv){
    int where_from = 0;
    for(int i=0;i<route.size();i++){
        if(route[i].second == to_find){
            if(route[i].first == arv) return arv;
            where_from = find_from(route[i].first,arv);
            break;
        }
    }
    return where_from;
}

void cut_branch(){//从route去掉一条边，从这个边的下一个边开始搜索
    int i = route.back().first;
    int j = route.back().second;
    route.pop_back();
    visited_d[i] = false;
    visited_a[j] = false;  
    cost_p -= cost[i-1][j-1];  
    edge_p = indices.back();
    distance_p-=graph[edge_p].first;
    indices.pop_back();
}

void TSP(int& edge_p,int& distance_p,int&cost_p){
    int dep = graph[edge_p].second/n+1;
    if(visited_d[dep]) return;
    int arv = graph[edge_p].second%n+1;
    if (visited_a[arv]) return;
    if (cost_p+cost[dep-1][arv-1]>L) {
        return;
    }
    //检查是否形成回路
    if(arv == find_from(dep,arv)) 
        return ;
    if(distance_p + graph[edge_p].first*(n-1-route.size()) > s_dis){
        if(route.empty())
            return;
        cut_branch();
        return;
    } else {
        distance_p += graph[edge_p].first;
        cost_p += cost[dep-1][arv-1];
        visited_d[dep] = true;
        visited_a[arv] = true;
        route.push_back(make_pair(dep,arv));
        indices.push_back(edge_p);
        if(route.size() == n-1) {
            s_dis = distance_p;
            vector <int> sorted;
            int index = 0;
            //找道路的起点
            for(int i=1;i<=n;i++){
                if(visited_a[i] == false){
                    sorted.push_back(i);
                    index = i;
                    break;
                }
            }
            //再sort
            while(sorted.size()!=n){
                for(int i=0;i<n-1;i++){
                    if(route[i].first == index){
                    index = route[i].second;
                    sorted.push_back(index);
                    break;
                    }
                }
            }
            c_route.push_back(sorted);
            //근데 이게 무조건 두개를 빼지 않아야 될떄도 있음. 예를 들어서 
            //예를들어서, 그 graph에서 마지막노드와 그뒤에위치한 노드들의 w값이 같을 수도 있음
            cut_branch();      
            return;
        } else {//그게 아니라면, 인덱스를 추가시킨다. 그리고 다시 TSP
        //우선, 이런방식으로 DFS를하다보면 언제끝내야되는지가 관건임!
        //일단 가지치기를 해야되는경우를 알아보자
        // 1 : 이 노드의 w값으로 route에 자리들을 다 채워도 distance가 s_dis를 넘어설때 
        // -> route에서 마지막노드를 뺴고, 그 노드 기점으로 다음 노드부터 DFS탐색에 집어넣어, (limit새우고 하는건 의미없음)

        // 2 : index_p가 graph의 마지막 원소까지 탐색해버렸을때
        // -> route에서 마지막 노드빼고, 그 노드 기점으로 다음 노드부터 DFS탐색에 집어넣어
        // -> 그런데, 만약 마지막 노드뺴기전에 애초에route.size()가 0 이면? 탐색이 끝난거지
        // -> 여기서 드는 의문, 애초에 route의 원소개수가 n-1개여야지만 c_route가 될 수있음, 그럼 만약 route.size()가 0이 아닐때,
        // 맨 마지막 노드 뺸후, route남아있는 원소 갯수 + 앞으로 탐색할수있는 노드후보 갯수 가 n-1보다 적으면, 답이 없지않아?
        // 여기서 또 질문, 그럼 이상황에는 return 해야 할까, 아님 index_p를 조정해서 다시 DFS해야할까?
        // 다시 조정해야됌! 물론 그 상황에 부합하는게 많지는 않겠지만, 다시 조정해서,c_route를 찾아낼수 있을수도있음
        //
            while(edge_p < graph.size()-1){
                while(edge_p < graph.size()-1){
                    edge_p+=1;
                    TSP(edge_p,distance_p,cost_p);
                }
                if(route.size()==0) {
                    edge_p = graph.size()-1;
                    return;
                }
                cut_branch();
                if(route.size() + graph.size()-edge_p<n) {
                    if(route.size()==0){
                        edge_p = graph.size()-1;
                        return;
                    } 
                    cut_branch();
                }
            }
        }
    }
}

int main(){
    cin>>n>>L;
    //输入城市间道路长度,받으면서 정렬해버려
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>map[i][j];
            if(i!=j) graph.__emplace_back(make_pair(map[i][j],n*i+j));
        }
    }
    sort(graph.begin(),graph.end());
    //交通费用
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>cost[i][j];
        }
    }//첫번째 원소에 도시, 두번째 원소에 길이를 넣을것임
    TSP(edge_p,distance_p,cost_p);
    if (c_route.size() ==0 ){
        cout<<-1;
        return 0;
    }
    //总长度
    cout<<s_dis<<endl;
    //编号序列（含起点与终点）
    //如果存在多条满足花费限制的最短路线，请输出使得该编号序列字典序最小的一条。
    sort(c_route.begin(),c_route.end());
    for(iter = c_route[0].begin(); iter!=c_route[0].end();iter++){
        cout<<*iter<<" ";
    }
    return 0;
}


//https://docs.qq.com/doc/DRk9US01TYXhkTmVL