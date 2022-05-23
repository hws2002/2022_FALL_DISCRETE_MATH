#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <cstring>
using namespace std;

//用PT图
vector<pair<int, double> > *recipe;
double *T;//最早完成时间
double get_T(int n);
double required_time(double v,double s,double num_material);

double required_time(double v,double s,double num_material){
    long t=0;//cycle
    while(v*s*(((t+1)*t)/2)<=num_material){
        t++;
    }
    t--;
    double built = v*s*(((t+1)*t)/2);
    double remainder = (((num_material - built)/(v*(t+1)))*100)/100.0;
    return t*s+remainder;
}

//自顶向下求出最
//T（i) = max{(r_time)1 +T(tech_index)1,(r_time)2,T(tech_index)2,...,(r_time)Pi+T(tech_index)Pi}

double get_T(int n){
    if(T[n]>=0) return T[n];//如果该技术的最早获得时间已求，return该值
    double res = 0;
    for(int i=0;i<recipe[n].size();i++){
        double dis = ((get_T(recipe[n][i].first)+recipe[n][i].second)*100)/100.0;//求到这个结点的最长距离-》获得这个技术的最早时间
        if(res<dis){
            res = dis;
        }
    }
    T[n] = res;
    return res;
}

int main(){
    int num_tech;
    cin>>num_tech; 
    double * productivity;
    double * make_line;
    productivity = new double[num_tech+1];
    make_line = new double[num_tech+1];
    T = new double[num_tech+1];
    memset(T,-1,sizeof(double)*(num_tech+1));
    recipe = new vector<pair<int, double> >[num_tech+1];

    for(int i=1;i<num_tech;i++){//储存 单线生产速率v
        cin>>productivity[i];
    }
    for(int i=1;i<num_tech;i++){//储存 新建一条产线所需时间s
        cin>>make_line[i];
    }

    int new_index = 0;
    for(int i=1;i<=num_tech;i++){//储存 recipe
        int pi;
        cin>>pi;
        if(pi == 0){
            recipe[i].__emplace_back(make_pair(0,0));
            T[i] = 0;
        }
        else {
            for(int j=1;j<=pi;j++){
            int tech_index; double num_material;
            cin>>tech_index>>num_material;
            double v = productivity[tech_index];
            double s = make_line[tech_index];
            //时时求出从零基础生产该数量material需要的时间（required_time)
            double r_time = required_time(v,s,num_material);
            recipe[i].__emplace_back(make_pair(tech_index,r_time));
            }
        }
    }
    printf("%.2f",get_T(num_tech));

    delete[] T;
    delete[] productivity;
    delete[] make_line;
    delete[] recipe;
    return 0;
}