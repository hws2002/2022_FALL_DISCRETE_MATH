#include <iostream>
using namespace std;
struct Graphtype{
    int num;
    int **matrix;
    int *visited;
};
struct Queue{
    int *items;
    int front;
    int rear;
};

Graphtype* makeGraph(int numberofVertex){
    Graphtype* graph = new Graphtype[numberofVertex];
    graph->matrix = new int*[numberofVertex+1];
    graph->visited = new int(numberofVertex+1);
    graph->num = numberofVertex;
    for(int i=0;i<numberofVertex;i++){
        graph->matrix[i] = new int[numberofVertex];
        memset(graph->matrix[i],0,sizeof(int)*(numberofVertex+1));
        graph->visited[i] = 0;
    }
    return graph;
}

void deleteGraph(Graphtype *graph){
    delete[] graph->visited;
    for(int i=0;i<graph->num;i++){
        delete[] graph->matrix[i];
    }
    delete []graph->matrix;
}

Queue* createQueue(int n){
    Queue * newQueue = new Queue;
    newQueue->front = -1;
    newQueue->rear = -1;
    newQueue->items = new int[n];
    return newQueue;
}

void deleteQueue(Queue* q){
    delete q->items;
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

void insert_edge(Graphtype *g, int start, int end){
    g->matrix[start][end] = 1;
}
void BFS(Graphtype* g, int s,int n){
    Queue* queue = createQueue(n);
    int i;
    enQueue(queue,s);
    cout<<s<<endl;
    while(!isEmpty(queue)){
        s = deQueue(queue);
        for(i = s; i<g->num;i++){
            if(!g->visited[i]&&g->matrix[s][i] == 1){
                g->visited[i] = 1;
                enQueue(queue,i);
                cout<<i;
            }
        }
    }
    deleteQueue(queue);
}
void DFS(Graphtype* g, int s){

}
int main(){
    int n,m,s = 0;
    Graphtype* graph;//graph는 포인터다!!!
    cin>>n>>m>>s;// n, m, s，表示图的 结点数、图的 边数、搜索的开始结点。
    graph = makeGraph(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        insert_edge(graph,u,v);
    }
    BFS(graph,s,n);
    DFS(graph,s);
    deleteGraph(graph);
    return 0;
}


/*
1 ≤ n ≤ 200000, 1 ≤ m ≤ 1000000

1 ≤ s ≤ n

1 ≤ u, v ≤ n

注意：图 G 中可能存在重边和自环
*/