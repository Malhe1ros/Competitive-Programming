#include <bits/stdc++.h>
using namespace std;

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

/*
creates the upper hull of the points
*/


vector<Point> upper_hull(vector<Point>& pontos,bool _sort=false){
	if (_sort) sort(pontos.begin(),pontos.end());

	vector<Point> ans;
	ans.push_back(pontos[0]);
	for (int i=1;i<pontos.size();i++){
		//to avoid adding equal points

		if (ans.size()==1 || cross(ans[ans.size()-2],ans.back(),pontos[i])<0){
			if (pontos[i]!=ans.back())ans.push_back(pontos[i]);
		}
		else{
			// >= to avoid adding colinear points
			while(ans.size()>=2 && cross(ans[ans.size()-2],ans.back(),pontos[i])>=0){
				ans.pop_back();
			}
			// To avoid adding duplicates
			if (pontos[i]!=ans.back())ans.push_back(pontos[i]);
		}
	}
	return ans;
}

/*
creates the down hull of the points;
*/

vector<Point> down_hull(vector<Point>& pontos,bool _sort=false){
	if (_sort) sort(pontos.begin(),pontos.end());
	vector<Point> ans;
	ans.push_back(pontos[0]);
	for (int i=1;i<pontos.size();i++){
		if (ans.size()==1 || cross(ans[ans.size()-2],ans.back(),pontos[i])>0){
			//to avoid adding equal points
			if (pontos[i]!=ans.back())ans.push_back(pontos[i]);
		}
		else{
			// >= to avoid adding colinear points
			while(ans.size()>=2 && cross(ans[ans.size()-2],ans.back(),pontos[i])<=0){
				ans.pop_back();
			}
			// To avoid adding duplicates
			if (pontos[i]!=ans.back())ans.push_back(pontos[i]);
		}
	}
	return ans;
}




vector<Point> convex_hull(vector<Point>& pontos){
    sort(pontos.begin(),pontos.end());
    auto uh=upper_hull(pontos);
    auto dh=down_hull(pontos);
    vector<Point> ansf;
    for (int i=0;i<dh.size();i++){
        ansf.push_back(dh[i]);
    }
    int n=uh.size();
    for (int i=n-2;i>=1;i--){
        ansf.push_back(uh[i]);
    }
    return ansf;
}

int dot(Point a,Point b){
	return a.x*b.x+a.y*b.y;
}

//DO NOT INSERT THE SET OF POINTS, INSERT THE SORTED UPPER HULL AND THE SORTED LOWER HULL;
//USE THE OTHER FUNCTION
Point farthest_point(Point dir,vector<Point> v){
    int b=0;
	int e=v.size()-1;
	int melhor=0;
	while(b<e){
		if (b>=e) break;
		int test1=b+(e-b)/3;
		int test2=e-(e-b)/3;
		int d1=dot(dir,v[test1]);
		int d2=dot(dir,v[test2]);
		if (d2>d1){
			b=test1+1;
			melhor=test2;
		}
		else{
			e=test2-1;
			melhor=test1;
		}
	}
	return v[melhor];
}
/*
to calculate the farthest point of a set of points use farthest_point(dir,lower_hull) and farthest_point(dir,upper_hull); 
We want to maximize the dot product of dir and some other vector (i am using the as points, because the vectors are from the origin, so it doesn't matter, i just need a pair)
*/
Point farthest_point(Point dir,vector<Point> uh,vector<Point> dh){
	auto t1=farthest_point(dir,uh);
	auto t2=farthest_point(dir,dh);
	if (dot(dir,t1)>dot(dir,t2))return t1;
	else return t2;
}
double dist(Point a,Point b){
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int main(){
	
}
