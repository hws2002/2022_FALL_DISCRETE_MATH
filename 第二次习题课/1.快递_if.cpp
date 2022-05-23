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

void TSP(int& edge_p, int& distance_p,int& cost_p){
    if(edge_p == graph.size()){//시작점이 graph.size까지 올리가 없음!
        cut_branch();
        TSP(++edge_p,distance_p,cost_p);
    }
    if(route.size() ==0){
        if(graph[edge_p].first * (n-1) <= s_dis && edge_p<=(n-1)*(n-1)){//可以执行
            int dep =graph[edge_p].second/n +1;
            int arv =graph[edge_p].second%n +1;
            if(cost[dep-1][arv-1]>=L) {
                TSP(++edge_p,distance_p,cost_p);
            } else {
                visited_d[dep] = true;
                visited_a[arv] = true;
                distance_p += map[dep-1][arv-1];
                cost_p += cost[dep-1][arv-1];
                route.__emplace_back(make_pair(dep,arv));
                indices.__emplace_back(edge_p);
                TSP(++edge_p,distance_p,cost_p);
            }
        } else{
            return;//완전 끝나버린거임!
        }
    } else { //시작점이 아니라면,
        if(distance_p + graph[edge_p].first *(n-1-route.size()) > s_dis){
            //가지치기 드가자
            cut_branch();
            TSP(++edge_p,distance_p,cost_p);
        } else {
            int dep =graph[edge_p].second/n +1;
            int arv =graph[edge_p].second%n +1;
            if(cost_p + cost[dep-1][arv-1]>L||visited_d[dep]==true||visited_a[arv] == true|| arv==find_from(dep,arv)){
                TSP(++edge_p,distance_p,cost_p);
            } else {
                visited_d[dep] = true;
                visited_a[arv] = true;
                distance_p+=map[dep-1][arv-1];
                cost_p+=cost[dep-1][arv-1];
                route.__emplace_back(make_pair(dep,arv));
                indices.__emplace_back(edge_p);
                if(route.size() == n-1){
                    s_dis = distance_p;
                    vector <int> sorted;
                    int index = 0;
                    //找道路的起点
                    for(int i=1;i<=n;i++){
                        if(visited_a[i] == false){
                            sorted.__emplace_back(i);
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
                    if( edge_p < graph.size()-1 && graph[edge_p+1].first == graph[edge_p].first){
                        cut_branch();
                    } else{
                        cut_branch();
                        cut_branch();
                    }
                }
                TSP(++edge_p,distance_p,cost_p);
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