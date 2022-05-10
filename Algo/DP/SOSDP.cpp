#include <bits/stdc++.h>
 
using namespace std;
 
#define ld long double
#define ll long long
#define int ll
#define FF first.first
#define FS first.second
#define SF second.first
#define SS second.second
#define PB push_back
#define MP make_pair
#define all(cont) cont.begin(),cont.end()
#define rall(cont) cont.rbegin(), cont.rend()
#define FOR(i, j) for(int i=0;i<j;i++)
#define GO cin.tie(NULL);
#define FAST ios_base::sync_with_stdio(false);
#define AE cout<<"AEEEE"<<endl;
#define _L cout<<"Linha "<<__LINE__<<endl;
#define sz(x) (int)x.size()
 
typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;
typedef vector<VI> VVI;
 
const long double PI = 3.14159265359;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll a, ll b){return uniform_int_distribution<ll>(a, b)(rng);}
 
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}
 
void print(vector<int>v){
	cout<<"[";
	FOR(i,sz(v)){
		cout<<v[i];
		if(i+1!=sz(v))cout<<", ";
	}
	cout<<"]"<<endl;
}
 
void print(pii p){
	cout<<"{"<<p.first<<", "<<p.second<<"}"<<endl;
}
 
template<typename Container>
void print(Container beg){
    cout<<"[";
    for(auto k:beg){
        cout<<k<<" ";
    }
    cout<<"]"<<endl;
}
const int N=20;
const int maxn=(1<<20);
int A[maxn];
int F[maxn];
int B[maxn];
int G[maxn];
int C[maxn];
int H[maxn];
int inv(int a){
  return maxn-1-a;
}
void SOS1(){
      for(int i = 0; i<(1<<N); ++i)
        F[i] = A[i];
    for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
        if(mask & (1<<i))
            F[mask] =F[mask] + F[mask^(1<<i)];
    }
}
void SOS2(){
      for(int i = 0; i<(1<<N); ++i)
        G[i] = B[i];
    for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
        if(mask & (1<<i))
            G[mask] =G[mask] + G[mask^(1<<i)];
    }
}
 
 
//problem is to print for all x
//number of y such that x|y=x (submask)
//number of y such that x&y==x (supermask)
//number of y such that x&y!=0 (share 1 bit with me)
signed main(){
  GO FAST
  int n;cin>>n;
  VI v(n);
  FOR(i,n)cin>>v[i];
  FOR(i,n){
    A[v[i]]++;
    B[inv(v[i])]++;
  }
  SOS1();
  SOS2();
  FOR(i,n){
    cout<<F[v[i]]<<" "<<G[inv(v[i])]<<" "<<n-F[inv(v[i])]<<'\n';
  }
}
