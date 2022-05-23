#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;
std::vector<int>::iterator iter;
vector<vector<int> > c_route;
vector<pair<int,int> > route;

void make_sorted(vector<int> &sorted, int index){
    while(sorted.size()!=4){
        for(int i=0;i<3;i++){
            if(route[i].first == index){
                index = route[i].second;
                sorted.push_back(index);
                break;
            }
        }
    }
}

int main(){

    // vector<pair<int,int> > v;
    // v.push_back(make_pair(1,3));
    // v.push_back(make_pair(1,1));
    // v.push_back(make_pair(1,2));
    // sort(v.begin(),v.end());
    // for (int i = 0; i < v.size(); i++) 
    //     cout << get<0>(v[i]) << " " << get<1>(v[i]) <<endl;
    // cout<<v.size();
    // v.clear();
    // cout<<v.size();

    //    vector<vector<int> > c_route;
    //      vector<int> route;
    // for(int i=1;i<5;i++){
    //     route.push_back(i);
    // }    
    // c_route.push_back(route);
    // for(iter = c_route[0].begin(); iter!= c_route[0].end(); iter++)
    // {
    //     std::cout<< *iter << std::endl;
    // }
    // route.clear();
    // for(int i=0;i<4;i++){
    //     route.push_back(i);
    // }
    //     c_route.push_back(route);
    // sort(c_route.begin(),c_route.end());
    // for(iter = c_route[0].begin(); iter!= c_route[0].end(); iter++)
    // {
    //     std::cout<< *iter << std::endl;
    // }
    route.push_back(make_pair(4,3));
    route.push_back(make_pair(1,4));
    route.push_back(make_pair(3,2));    
    vector <int> sorted;
    int index = 1;
    sorted.push_back(1);//시작도시 넣기
    //시작도시찾았으면, route에서 시작도시를 first원소로 가고있는 pair를 찾아서, 그 pair의 second원소를 sorted에 넣은후에, index = pair.second 저장해두기
    //다시 route에서 시작도시를 first원소로 가지고 있는 pair 찾고, 그pair의 second 원소를 sorted에 넣은후에, index = pair.second
    //계속 실행해서, 마지막에 sorted.size()가 n이 될떄까지
    //--> 결국 递归라는걸 알 수 있음
    cout<<c_route[0];
    make_sorted(sorted,index);
    c_route.push_back(sorted);
    return 0;
}