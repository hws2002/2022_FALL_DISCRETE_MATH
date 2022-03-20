#include <iostream>
#include <cstring>
using namespace std;
struct Queue{
    int *items;
    int front;
    int rear;
};

Queue* createQueue(int m){
    Queue* newQueue = new Queue;
    newQueue->front = 0;
    newQueue->rear = 0;
    newQueue->items = new int[m];
    return newQueue;
}

int isEmpty(Queue*queue){
    return queue->rear == queue->front; //공백상태
}

void enQueue(Queue* queue, int vertex){
    queue->rear++;
    queue->items[queue->rear] = vertex;
}

int deQueue(Queue* queue){
    queue->front++;
    return queue->items[queue->front];
}

int r_deQueue(Queue* queue){
    return queue->items[queue->rear--];
}
//enQueue,deQueue이런식으로 구현하면, front, rear 가 계속 증가할수밖에없음,
//그러면 Segmentation Fault가 생길수도!
//items은 capacity가 n인데, front, rear가 n보다 커질 수 있다는 얘기!
//충분히 발생할 수 있는 이유 : 重边，自环을 포함하니까!

void BFS(int s,Queue* M_queue,Queue* s_queue,int n){
    int* visited = new int[n+1];
    memset(visited,0,sizeof(int)*(n+1));
    enQueue(M_queue,s);
    cout<<s<<" ";
    visited[s] = 1;
    int i;
    while(!isEmpty(M_queue)){
        s = deQueue(M_queue);
        if(s_queue[s].rear == 0){
            if(!visited[s]){
                visited[s] = 1;
                cout<<s<<" ";
            }
            continue;
        }
        for(i = s_queue[s].rear;i > 0;i--){
            int v = s_queue[s].items[i];
            if(!visited[v]){
                visited[v] = 1;
                enQueue(M_queue,v);
                cout<<v<<" ";
            }
        }
    }
    delete[] visited;
}
/*
void DFS(int s,Queue* N_queue,Queue* s_queue,int n){
    int *visited2 = new int[n+1];
    memset(visited2,0,sizeof(int)*(n+1));
    enQueue(N_queue,s);
    while(!isEmpty(N_queue)){
        int u = r_deQueue(N_queue);//N_queue에서 뽑는걸 뒤에서 뽑아!
        if(visited2[u]){continue;}
        visited2[u] = 1;
        cout<<u<<" ";
        for(int i = 1;i<=s_queue[u].rear;i++){//N_queue에 뒤에서 넣는데, s_queue의 앞에서부터 뽑아서 넣어!
            int next = s_queue[u].items[i];
            enQueue(N_queue,next);
        }
    }
    delete[] visited2;
}
*/
//递归
void DFS(int s,Queue* s_queue,int * visited){
    if(visited[s]) return;
    visited[s] = 1;
    cout<<s<<" ";
    for(int i=s_queue[s].rear;i>0;i--){
        int next = s_queue[s].items[i];
        DFS(next,s_queue,visited);
    }
}


//s_queue[1] 은 1을 시작점으로 하는 모든 vertex들의 종점을 items에 담아둔 queue의 주소!

int main(){
    int n,m,s = 0;
    cin>>n>>m>>s;// n, m, s，表示图的 结点数、图的 边数、搜索的开始结点。
    Queue* s_queue = new Queue[n+1];//front, rear 초기화가 0으로 됨!
    for(int i = 0; i<n+1; i++){
        s_queue[i].items = new int[m];
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;//u,v <=n
        enQueue(&s_queue[u],v);
    }
    //工作结点을 쌓을M_queue，N_queue 생성
    Queue* M_queue = createQueue(m);
    BFS(s,M_queue,s_queue,n);
    //释放内存
    delete[] M_queue->items;
    delete M_queue;

    cout<<endl;
    int *visited = new int[n+1];
    memset(visited,0,sizeof(int)*(n+1));
    
    DFS(s,s_queue,visited);
    delete [] visited;
    for(int i=0;i<n+1;i++){
        delete[] s_queue[i].items;
    }
    delete[] s_queue;    
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