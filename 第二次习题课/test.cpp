#include <iostream>
#include <bitset>
#include <typeinfo>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;
int twoConvertTen(int num){
    int res = 0, mul = 1;
    while(num>0){
        if(num%2)
            res +=mul;
        mul *= 2;
        num /= 10;
    }
    return res;
}
pair <bitset<4>, int> path[4];
vector <int>::iterator iter;
void add(int a,int b){
    cout<<a<<" "<<b;
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

int discordance(bitset<4> keyboard){//이거 구해야됨!
    if(keyboard.count()<=1) return 0;
    vector <int> on;
    for(int i=4;i>=0;i--){
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

int main(){
    bitset<4> start_b("0000");
    bitset<4> start_c("0010");
    vector <int>v;
    v.push_back(0);
    v.push_back(4);
    v.push_back(5);
    v.push_back(8);
    int num1 = 1000;
    int num2 = 6;
    int num3 = num1 ^ num2;
    cout<<num3<<endl;
    // cout<<start<<endl;
    // cout<<start.to_ulong()<<endl;
    // cout<<start.size()<<endl;
    // bitset<14>start1 = start.flip(0);
    // cout<<start1<<endl;
    // cout<<start<<endl;
    // int start = start_b.to_ulong();
    // start_b.flip(0);
    // vector <pair <bitset<14>, int> > graph[4];
    // graph[start].__emplace_back(make_pair(start_b,100));
    // for(int i=1;i<4;i++){
    //     start_b.flip(i-1);
    //     graph[start].__emplace_back(make_pair(start_b.flip(i),100));
    // }
    // path[2] = make_pair(start_b,100);
    // // for(iter = v.begin();iter != v.end();iter++){
    // //     cout<<add(*iter);
    // // }
    // cout<<path[2].first<<endl;
    // vector <int> ::iterator iter1;
    // vector <int> ::iterator iter2;
    //     for(iter1 = v.begin();iter1!=v.end();iter1++){
    //         for(iter2 = iter1+1;iter2!=v.end();iter2++){
    //             add(*iter1,*iter2);
    //             cout<<endl;
    //         }
    //     }
    bitset<4> s("1101");
    cout<<s.to_ulong()<<endl;;
    cout<<discordance(s)<<endl;
    return 0;
}
