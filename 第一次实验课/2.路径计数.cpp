#include <iostream>
using namespace std;

int main(){
    unsigned long long n,m,s,t,k;//图的结点数、图的边数、道路的始点、道路的终点、道路经过的边数。
    unsigned long long matrix[101][101] = {0};
    cin>>n>>m>>s>>t>>k;
    for(unsigned long long i=0;i<m;i++){
        unsigned long long u,v;
        cin>>u>>v;
        matrix[u][v] +=1;
    }
    //A^k 를 구해야하는데, 굳이 다 구할 필요 없음!A^i, i<=k-1의 s번째 항만 구하고, 마지막에 A^k에서 a<s,t>만 구하면 끝!
    unsigned long long A_s[101] = {0};
    for(unsigned long long i=1;i<n+1;i++){
        A_s[i] = matrix[s][i];
    }
    for(unsigned long long i=0;i<k-2;i++){
        unsigned long long res[101] = {0};
        for(unsigned long long j=1;j<n+1;j++){
            for(unsigned long long x=1;x<n+1;x++){
                res[j] += (A_s[x]*(matrix[x][j]))%1000003;
            }
        }
        for(unsigned long long j=1;j<n+1;j++){
            A_s[j] = res[j];
        }
    }
    unsigned long long res=0;
    for(unsigned long long i=1;i<n+1;i++){
        res += A_s[i]*(matrix[i][t])%1000003;
    }
    cout<<res%1000003;
    return 0;
}

/*
1 ≤ n ≤ 100, 1 ≤ m ≤ 10000

1 ≤ s, t ≤ n

1 ≤ k ≤ 100

注意：图 G 中可能存在重边和自环，s 和 t 可能为同一个结点
*/