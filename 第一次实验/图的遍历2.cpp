#include <iostream>
using namespace std;
struct Queue{
    int *items;
    int front;
    int rear;
};
Queue* createQueue(int n){
    Queue * newQueue = new Queue;
    newQueue->front = -1;
    newQueue->rear = -1;
    newQueue->items = new int[n];
    return newQueue;
}

void deleteQueue(Queue* q){
    delete[] q->items;
    delete q;
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

void DFS(){
    
}

//s_queue[1] 은 1을 시작점으로 하는 모든 vertex들의 종점을 items에 담아둔 queue의 주소!

int main(){
    int n,m,s = 0;
    cin>>n>>m>>s;// n, m, s，表示图的 结点数、图的 边数、搜索的开始结点。
    //工作结点을 쌓을M_queue 생성
    Queue*M_queue = createQueue(n);
    Queue*s_queue;//front, rear 초기화가 0으로 됨!
    s_queue = new Queue[n+1];
    for(int i = 0; i<n+1; i++){
        s_queue[i].items = new int[n+1];
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        enQueue(&s_queue[u],v);
    }
    BFS(s,M_queue,s_queue,n);
    cout<<endl;
    DFS();
    for(int i=0;i<n+1;i++){
        delete[] s_queue[i].items;
    }
    delete[] s_queue;
    deleteQueue(M_queue);
    return 0;
}