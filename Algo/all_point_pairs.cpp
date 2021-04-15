#include <bits/stdc++.h>
using namespace std;
//#define double long double
struct Point{
    int x,y;
    Point(){

    }
    Point(int a,int b){
        x=a;
        y=b;
    }
    bool operator< (const Point & other){
        if (other.x==x)return y<other.y;
        return x>other.x;
    }
    bool operator!= (const Point & other){
        return other.x != x || other.y!=y;
    }
    bool operator==(const Point & other){
        return other.x == x && other.y==y;
    }
};
struct Vetor{
    int x,y;
    //creates vector from a to b
    Vetor(){

    }
    Vetor(Point a,Point b){
        x=b.x-a.x;
        y=b.y-a.y;
    }
    int cross(Vetor other){
        return x*other.y-y*other.x;
    }
    Point conv(){
        int rx=-y;
        int ry=x;
        if (ry<0){
            return Point(-rx,-ry);
        }
        if (ry==0 && rx<0)return Point(-rx,ry);
        return Point(rx,ry);
    }
};
/*
Creates vector from A to B and from A to C
Return:
negative if A->B to the left of A->C;
zero if collinear;
positive if A->B to the right of A->C;
*/
int cross(Point a,Point b,Point c){
    return Vetor(a,b).cross(Vetor(a,c));
}

bool cmp(Point a,Point b){
    return cross(Point(0,0),a,b)>0;
}
bool cmp1(pair<Point,pair<Point,Point>> a,pair<Point,pair<Point,Point>> b){
    if (a.first==b.first){
        if(a.second.first==b.second.first){
            return a.second.second<b.second.second;
        }
        return a.second.first<b.second.first;
    }
    return cmp(a.first,b.first);
}

void polar_sort(vector<Point>&v){
    sort(v.begin(),v.end(),cmp);
}
double area(vector<Point> v,int a,int b,int c){
    if (c<0 || c==v.size()) return 1e18;
    return abs((double)cross(v[a],v[b],v[c]))/2;
}

pair<int,int> ptp(Point a){
    return {a.x,a.y};
}

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};
  

//it will return 0 in case there are collinear points
double min_triangle(vector<Point> &v,int n){
    vector<pair<Point,pair<Point,Point>>> novo;
    sort(v.begin(),v.end());
    for (int i=0;i<n;i++){
        for (int j=i+1;j<n;j++){
            novo.push_back({Vetor(v[i],v[j]).conv(),{v[i],v[j]}});
        }
    }
    unordered_map<pair<int,int>,int,hash_pair> hash;
    for (int i=0;i<n;i++){
        hash[ptp(v[i])]=i;
    }

    sort(novo.begin(),novo.end(),cmp1);
    double min_area=1e18;
    int abbb;
    cout<<novo.size()<<endl;
    for (int i=0;i<novo.size();i++){
        auto p1=novo[i].second.first;
        auto p2=novo[i].second.second;
        int index1=hash[ptp(p1)];
        int index2=hash[ptp(p2)];
        int mini=min(index1,index2);
        int maxi=max(index1,index2);
        int teste1=mini-1;
        int teste2=maxi+1;
        min_area=min(min_area,area(v,index1,index2,teste1));
        min_area=min(min_area,area(v,index1,index2,teste2));
        swap(v[index1],v[index2]);
        hash[ptp(p1)]=index2;
        hash[ptp(p2)]=index1;
        
    }
    return min_area;

}

int main(){
    cout<<fixed;
    while(1){
    int n;scanf("%d",&n);
    if (n==0) break;
    vector<Point>v(n);
    for (auto &k:v)scanf("%d%d",&k.x,&k.y);
    cout<<min_triangle(v,n)<<endl;
    }

}