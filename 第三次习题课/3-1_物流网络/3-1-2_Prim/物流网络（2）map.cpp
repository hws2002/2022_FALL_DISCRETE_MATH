#include <iostream>
#include <vector>  // std::vector
#include <algorithm>  // std::sort
#include <cmath>
#include <map>
#include <climits>

using namespace std;

int X[20 + 1], Y[20 + 1];

long long calc_cost(int i, int j) {
    // !!! TODO: 你的代码 !!!
    //i번쨰 노드랑 j번쨰 노드의 거리를 구하는거임!
    long long res =  pow((abs(X[i] - X[j])),3) + pow((abs(Y[i] - Y[j])),3);
    return res;
}

bool cmp(pair<int, long long>& a, pair<int, long long>&b ){
    return a.second<b.second;
}

void sort(map<int, long long>& map){
    vector<pair<int, long long> > vec;
    for(auto& it : map){
        vec.emplace_back(it);
    }
    sort(vec.begin(),vec.end(),cmp);
}
int n;

bool visited[20+1] = {false};
int main(){
    map<int, long long> edge[20+1];
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>X[i]>>Y[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            edge[i].insert(make_pair(j,calc_cost(i,j)));
        }
        sort(edge[i]);
    }
    std::map<int, long long>::iterator it;
    for(int i=1;i<=n;i++){
        for(it = edge[i].begin();it !=edge[i].end();++it){
            cout<<it->first<<" "<<it->second<<" ";
        }
        cout<<endl;
    }
    vector<int> nodes;
    long long total_cost = 0;
    int went = 1;
    nodes.push_back(went);
    visited[1] = true;
    while(nodes.size()!=4){
        long long shortest = LLONG_MAX;
        int index = 0;
        std::map<int, long long>::iterator ptr;
        for(int i=0;i<nodes.size();i++){
            ptr = edge[nodes[i]].begin();
            while(visited[ptr->first] == true){
                ptr++;
            }
            if(shortest>ptr->second){
                shortest = ptr->second;
                index = nodes[i];
            }
        }
        total_cost += shortest;//ptr->second
        went = ptr->first;
        nodes.push_back(went);
        visited[went] = true;
        // edge[index].erase(ptr);
        // edge[went].erase(edge[went].find(index));
    }
    cout<<endl;
    cout<<total_cost<<endl;
    cout<<endl;
    vector<int>::iterator ptr;
    for(ptr = nodes.begin();ptr!=nodes.end();++ptr){
        cout<<*ptr<<" ";
    }
    cout<<endl;
    cout<<endl;
        for(int i=1;i<=n;i++){
        for(it = edge[i].begin();it !=edge[i].end();++it){
            if(visited[it->first] == false)
                cout<<it->first<<" "<<it->second<<" ";
        }
        cout<<endl;
    }
    return 0;
}