#include <iostream>
#include <vector>
using namespace std;
int point_start[10005]={0};
int point_end[10005]={0};
int matrix[105][105] = {0};
int first_block_num[105] = {0};
int table_weight[10005] = {0};
int edges_index[101] = {0};

int main(){
    int N,M=0;
    cin>>N>>M;
    //输入数据
    vector<int> *edges = new vector<int>[N+1];
    for(int i=1;i<N+1;i++){
        edges[i].push_back(0);
    }
    for (int i=1; i<M+1;i++){
        int u, v, w;
        cin>>u>>v>>w;
        point_start[i] = u; point_end[i] = v;table_weight[i] = w; edges[u].push_back(i);
        if(matrix[u][v]==0)
            matrix[u][v] = w;
        else 
            matrix[u][v] = -1;
        first_block_num[u] = i;
    }
    //邻接矩阵输出
    for(int i=1;i<N+1;i++){
        for(int j=1;j<N+1;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    //邻接表输出
    //表结点编号输出
    for(int i=1;i<N+1;i++){
        cout<<first_block_num[i]<<endl;
    }
    
    //表结点输出
    for(int i=1;i<M+1;i++){
        int u = point_start[i];
        int v = point_end[i];
        int w = table_weight[i];
        int index = edges_index[u];
        cout<<v<<" "<<w<<" "<<edges[u][index]<<endl;
        edges_index[u]+=1;
    }
    delete[] edges;
    return 0;
}

/*
在本题中，“邻接表”定义为 n 个 单向链表，分别对应以每个结点为始点的边集合，其中：
终点编号 x、边权值 w、下一个表结点编号 next
输入的第 i 条边的 表结点编号为 i；当表结点为其链表的最后一个结点时，next 的值为 0
每个链表的各结点顺序为 对应边在输入中的相反顺序，即，每个链表中的表结点为 编号从大到小 的顺序（想一想，这对编程实现有什么作用？）

√ 前 n 行每行一个整数，第 i 行表示第 i 个链表的 第一个表结点编号。如果该链表为空，则输出 0 

√ 后 m 行，第 i 行表示编号为 i 的 表结点 的信息，包含三个整数 x, w, next
*/