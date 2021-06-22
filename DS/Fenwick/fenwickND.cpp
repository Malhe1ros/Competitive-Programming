#include <bits/stdc++.h>

using namespace std;
#define ll long long

/*
    N dimensional BIT
    from https://usaco.guide/gold/PURS?lang=cpp#solution-2
    How to use:
    create BIT<ll,size1,size2>
    update values with update(x,y,value);
    query with query(x1,x2,y1,y2) [IDK WHY BUT PAY ATTENTION];
*/ 

template <class T, int ...Ns> struct BIT {
	T val = 0; void update(T v) { val += v; }
	T query() { return val; }
};
template <class T, int N, int... Ns> struct BIT<T, N, Ns...> {
	BIT<T,Ns...> bit[N+1];
	template<typename... Args> void update(int pos, Args... args) { assert(pos > 0);
		for (; pos<=N; pos+=pos&-pos) bit[pos].update(args...); }
	template<typename... Args> T sum(int r, Args... args) {
		T res=0; for (;r;r-=r&-r) res += bit[r].query(args...);
		return res; }
	template<typename... Args> T query(int l, int r, Args...
		args) { return sum(r,args...)-sum(l-1,args...); }
};
int main(){
    int n,m;cin>>n>>m;
    vector<vector<int>>v(n,vector<int>(n));
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            char c;cin>>c;
            if (c=='*'){
                v[i][j]=1;
            }
        }
    }
    BIT<ll,1001,1001> f= BIT<ll,1001,1001>();
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            f.update(i+1,j+1,v[i][j]);
        }
    }
    while(m--){
        int tt;cin>>tt;
        if (tt==1){
            int a,b;cin>>a>>b;
            v[a-1][b-1]=1-v[a-1][b-1];
            if(v[a-1][b-1]==0)f.update(a,b,-1);
            else f.update(a,b,1);
            
        }
        else{
        int a,b,c,d;cin>>a>>b>>c>>d;
        cout<<f.query(a,c,b,d)<<endl;
        }
    }

}
