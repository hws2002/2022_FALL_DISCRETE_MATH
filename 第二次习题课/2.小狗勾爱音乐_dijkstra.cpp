#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <bitset>
#include <cmath>
using namespace std;
    
/*
어떤 자료구조로 담을것인가
노드는 많은데, 간선은적음 -> 邻接表
*/
string str;
bool visited[16384] = {false};//是否访问过
int d[16384];//从起点到第i个结点的最短距离]
pair <int, int> path[16384];
vector <string> match;
int get_d(int u, int v);
int discordance(bitset<14> keyboard);
vector <string> response;

void get_path(pair <int,int> *path, int start){
    int now = path[0].first;
    int key = path[0].second;
    response.__emplace_back(match[key]);
    while(now != start){
        now = path[now].first;
        key = path[now].second;
        response.__emplace_back(match[key]);
    }
}

int get_d(int u, int v){
    int degree = u-v+1;
    if(degree ==3) return 3;
    else if ((degree==6) || (degree == 8) || (degree == 10)) return 4;
    else if(degree ==5) return 5;
    else if (degree == 4|| degree==12) return 6;
    else if(degree ==7) return 7;
    else if(degree == 2 || degree == 14) return 8;
    else return 1000;
}

int discordance(bitset<14> keyboard){//求不和谐度
    if(keyboard.count()<=1) return 0;
    vector <int> on;
    for(int i=13;i>=0;i--){
        if(keyboard[i] ==1)
        on.__emplace_back(i);
    }
    if(keyboard.count()==2){
        int u = on[0];
        int v = on[1];
        //u가 v 보다 크고, 클수록 왼쪽에 붙어있음
        return get_d(u,v);
    }
    else {
        vector <int> ::iterator iter1;
        vector <int> ::iterator iter2;
        int T[1001] = {0};
        for(iter1 = on.begin();(iter1+1)!=on.end();iter1++){
            for(iter2 = iter1+1;iter2!=on.end();iter2++){
                T[get_d(*iter1,*iter2)]+=1;
            }
        }
        int res = 0;
        if(T[3]%2 ==1) res = res^3;
        if(T[4]%2 ==1) res = res^4;
        if(T[5]%2 ==1) res = res^5;
        if(T[6]%2 ==1) res = res^6;
        if(T[7]%2 ==1) res = res^7;
        if(T[8]%2 ==1) res = res^8;
        if(T[1000]%2 ==1) res = res^1000;
        return res;
    }
}

int dijkstra(int start){
    priority_queue<pair< int, int > > pq; //거리, 노드인덱스(10진법 수)
    pq.push(make_pair(0,start)); // 시작 노드로 가기 위한 최단경로는 0
    d[start] = 0;
    while(!pq.empty()){
        int dist = -pq.top().first;//현재 노드까지의 비용
        int now = pq.top().second; //현재 노드 index
        pq.pop();
        if(d[now]<dist) // 이미 최단경로를 확인한 노드인 경우 패스
            continue;
        bitset<14> now_b(now);//2진법으로 나타낸거 가지고,
        // graph[now]구해야됨! 그래프 채우기!
        for(int j=0;j<14;j++){
            if(j-1>=0) now_b.flip(j-1);
            now_b.flip(j);
            int test = now_b.to_ulong();
            if (test == 0) { 
                path[0] = make_pair(now,j);
                visited[0] = true;
                d[test] = dist;
                return d[test];
            }
            if(visited[test] == true) continue;
            visited[test] = true;
            //test도시를 가본적없을떄!즉 pq에 들어가본적 없음!
            path[test]=(make_pair(now,j));//test라는 노드는, now_b라는 노드에서 j번쨰 비트를 flip하면 갈수있다(최단경로에서)
            //현재노드까지의 비용 + 다음 노드로 가는 비용 = 시도비용
            int cost = dist+discordance(now_b);
            // if(cost<d[w_node[now][i].first])//만약 시도 비용이 더 작다면 최단경로 테이블값을 갱신
            // 하지만 이미 이 도시는 처음가보는것이기떄문에,  시도비용 < INF, 무조건!!
            d[test] = cost;
            pq.push(make_pair(-cost,test));
        }
    }
    return -1;
}

int main(){
    match.push_back("F4");
    match.push_back("E4");
    match.push_back("D4");
    match.push_back("C4");
    match.push_back("B4");
    match.push_back("A4");
    match.push_back("G3");
    match.push_back("F3");
    match.push_back("E3");
    match.push_back("D3");
    match.push_back("C3");
    match.push_back("B3");
    match.push_back("A3");
    match.push_back("G2");
    cin>>str;
    bitset<14> start_b(str);
    int start = start_b.to_ulong();
    fill(d,d+16384,INT_MAX);
    int res = dijkstra(start);
    //PATH
    get_path(path,start);
    vector <string>::iterator ptr;
    for(ptr = response.end()-2;ptr >=response.begin();ptr--){
        cout<<*ptr<<" ";
    }
    cout<<endl;
    //路长
    cout<<res;
    return 0;
}
//https://hub1234.tistory.com/33
