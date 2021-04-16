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
        return x<other.x;
    }
    bool operator!= (const Point & other){
        return other.x != x || other.y!=y;
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

void polar_sort(vector<Point>&v){
    sort(v.begin(),v.end(),cmp);
}

int main(){
    int n;cin>>n;vector<Point>v(n);
    for (auto &k:v)cin>>k.x>>k.y;
    polar_sort(v);
    for (auto k:v){
            cout<<k.x<<" "<<k.y<<endl;
        }
}
