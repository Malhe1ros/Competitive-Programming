#include <bits/stdc++.h>
using namespace std;
/*
HOW TO USE:
PLEASE DON'T, I MEAN, IT HAS WORKED ON EVERY PROBLEM I NEEDED BUT I DON'T TRUST IT
IF YOU'RE BRAVE:
	just call point_inside(upper_hull(points,1),down_hull(points,1),POINT);
	it will return:
	1, if inside the convex hull,
	0, if on the border
	-1, if outside
*/

//ninf= negative infinite;
const int ninf=INT_MIN;
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
/*
return -1 if outside
return 0 if on border
return 1 if inside
*/
int point_inside_upper_hull(vector<Point> upper_hull,Point p){
	if (p.x<upper_hull[0].x || p.x>upper_hull.back().x) return -1;
	auto t=lower_bound(upper_hull.begin(),upper_hull.end(),Point(p.x,ninf));
	if (t==upper_hull.begin()){
		if(upper_hull[1].x==p.x){
		if(p.y==upper_hull[1].y)return 0;
		else if(p.y>upper_hull[1].y)return -1;
		else return 1;
		}
		else{
		if(p.y==upper_hull[0].y)return 0;
		else if(p.y>upper_hull[0].y)return -1;
		else return 1;
		}

	}
	auto teste=*t;
	t--;
	auto t1=*t;
	int testar=cross(teste,p,t1);
	if (testar>0) return -1;
	else if(testar==0) return 0;
	else return 1;
}

int point_inside_down_hull(vector<Point> upper_hull,Point p){
	if (p.x<upper_hull[0].x || p.x>upper_hull.back().x) return -1;
	auto t=lower_bound(upper_hull.begin(),upper_hull.end(),Point(p.x,ninf));
	if (t==upper_hull.begin()){
		if (t->x==p.x){
			if (t->y==p.y)return 0;
			if (t->y<p.y)return 1;
			return -1;
		}
	}
	auto teste=*t;
	t--;
	auto t1=*t;
	int testar=cross(teste,p,t1);
	if (testar<0) return -1;
	else if(testar==0) return 0;
	else return 1;
}

int point_inside(vector<Point> upper_hull,vector<Point> down_hull,Point p){
	int ans1=point_inside_upper_hull(upper_hull,p);
	int ans2=point_inside_down_hull(down_hull,p);
	//cout<<ans1<<" "<<ans2<<endl;
	if (ans1==-1 || ans2==-1) return -1;
	if (ans1==0 || ans2==0) return 0;
	return 1;
	
}
