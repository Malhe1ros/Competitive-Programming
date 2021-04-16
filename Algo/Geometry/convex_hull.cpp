#include <bits/stdc++.h>
using namespace std;

/*
How to use:
Create a vector of points and pass it to the convex_hull function
it will return the convex hull of the points (without equal and collinear points)[change sign to add collinear]
*/
//Can be used to solve https://open.kattis.com/submissions/7141168

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

vector<Point> upper_hull(vector<Point>& pontos){
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

vector<Point> down_hull(vector<Point>& pontos){
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
int main(){
	while(1){
		int n;cin>>n;
		if (n==0)break;
		vector<Point>v(n);
		for (auto &k:v){
			cin>>k.x>>k.y;
		}
		convex_hull(v);
	}
}
