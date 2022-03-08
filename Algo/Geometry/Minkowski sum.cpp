#include <bits/stdc++.h>
 
using namespace std;
#define int long long
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
	Point operator+(const Point& other){
		return Point(x+other.x,y+other.y);
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
	Vetor(){
 
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
 
Vetor getEdge(int u,vector<Point>&a){
	//cout<<u<<" "<<a.size()<<endl;
	auto p1=a[u];
	u++;
	if(u==a.size())u=0;
	auto p2=a[u];
	return Vetor(p1,p2);
}

 
vector<Point> minkowski(vector<Point>a,vector<Point> b){
	auto cha=convex_hull(a);
	auto chb=convex_hull(b);
	int l=0;
	int r=0;
	int N=cha.size();
	int M=chb.size();
	vector<Point> mink;
	mink.push_back(cha[0]+chb[0]);
	while(l<N || r<M){
		Vetor toad;
		if(l==N){
			toad=getEdge(r,chb);
			r++;
		}
		else if(r==M){
			toad=getEdge(l,cha);
			l++;
		}
		else{
			auto e1=getEdge(l,cha);
			auto e2=getEdge(r,chb);
			auto dir=e1.cross(e2);
			if(dir>0){
				toad=e1;
				l++;
			}
			else{
				toad=e2;
				r++;
			}
			
		}
		Point novo=mink.back()+Point(toad.x,toad.y);
		if(mink.size()>1 && cross(mink[mink.size()-2],mink.back(),novo)==0){
			mink.pop_back();
		}
		mink.push_back(novo);
	}
	mink.pop_back();
	return mink;
}
const int ninf=INT_MIN;
 
int point_inside_upper_hull(vector<Point>& uh,Point p){
	if (p.x<uh[0].x || p.x>uh.back().x) return -1;
	auto t=lower_bound(uh.begin(),uh.end(),Point(p.x,ninf));
	if (t==uh.begin()){
		if(uh[1].x==p.x){
		if(p.y==uh[1].y)return 0;
		else if(p.y>uh[1].y)return -1;
		else return 1;
		}
		else{
		if(p.y==uh[0].y)return 0;
		else if(p.y>uh[0].y)return -1;
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
 
int point_inside_down_hull(vector<Point>& uh,Point p){
	if (p.x<uh[0].x || p.x>uh.back().x) return -1;
	auto t=lower_bound(uh.begin(),uh.end(),Point(p.x,ninf));
	if (t==uh.begin()){
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
 
int point_inside(vector<Point>& uh,vector<Point>& dh,Point p){
	int ans1=point_inside_upper_hull(uh,p);
	int ans2=point_inside_down_hull(dh,p);
	//cout<<ans1<<" "<<ans2<<endl;
	if (ans1==-1 || ans2==-1) return -1;
	if (ans1==0 || ans2==0) return 0;
	return 1;
	
}
 
 
signed main(){
	vector<Point>v[3];
	for(int i=0;i<3;i++){
		int n;cin>>n;
		vector<Point>a;
		for(int j=0;j<n;j++){
			int b,c;cin>>b>>c;
			a.push_back(Point(b,c));
		}
		v[i]=convex_hull(a);
	}
	
	auto mink=minkowski(v[0],minkowski(v[1],v[2]));
	
	sort(mink.begin(),mink.end());
	auto uh=upper_hull(mink);
	auto dh=down_hull(mink);
	int t;cin>>t;
	
	while(t--){
		int a,b;cin>>a>>b;
		a*=3;
		b*=3;
		Point p(a,b);
		if(point_inside(uh,dh,p)>=0){
			cout<<"YES\n";
		}
		else cout<<"NO\n";
	}
}
