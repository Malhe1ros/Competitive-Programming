#include <bits/stdc++.h>
 
using namespace std;

 #include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

//to avoid hacking but when offline not necessary
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};


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
#define RFOR(i, j) for (int i=j;i>=0;i--)
#define GO cin.tie(NULL);
#define FAST ios_base::sync_with_stdio(false);
#define prec(x) cout << fixed << setprecision(x)
#define sz(x) (int)x.size()

typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;
typedef vector<VI> VVI;
typedef priority_queue<int> max_heap;
typedef priority_queue<pii> max_heapii;
typedef priority_queue<int,VI,greater<int>> min_heap;
typedef priority_queue<pii,VPII,greater<pii>> min_heapii;

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
	FOR(i,v.size()){
		cout<<v[i];
		if(i+1!=v.size())cout<<", ";
	}
	cout<<"]"<<endl;
}

void print(pii p){
	cout<<"{"<<p.first<<", "<<p.second<<"}"<<endl;
}
//#define int long long
#define LOG_MAXN 20
#define MAXN 1000010


inline int64_t HilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) return 0;
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = HilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}
 
struct Query {
	int l, r, idx; 
	int64_t ord;
 
	inline void calcOrder() {
		ord = HilbertOrder(l, r, LOG_MAXN, 0);
	}
};
 

vector<int> v;
 
int l=0;
int r=-1;//i have the answer calculated from l to r;
VI grafo[MAXN];
int resp=0;
int n,m;
int cor[MAXN];
VI euler;
int beg[MAXN];
int en[MAXN];
gp_hash_table<int,int,chash> occ;
gp_hash_table<int,int,chash> quem;
int dist=0;
void walkRLeft(){//removing r;

  quem[euler[r]]--;
  if (quem[euler[r]]&1){
    occ[cor[euler[r]]]++;
    if(occ[cor[euler[r]]]==1)resp++;
  }
  else{
    occ[cor[euler[r]]]--;
    if(occ[cor[euler[r]]]==0)resp--;
  }
  
  r--;
}
 
void walkRRight(){//adding r;
  r++;
  //occ[cor[r]]++;
  quem[euler[r]]++;
  if (quem[euler[r]]&1){
    occ[cor[euler[r]]]++;
    if(occ[cor[euler[r]]]==1)resp++;
  }
  else {
    occ[cor[euler[r]]]--;
    if(occ[cor[euler[r]]]==0)resp--;
  }


}
 
void walkLLeft(){//adding l;
  l--;
  quem[euler[l]]++;
  if(quem[euler[l]]&1){
    occ[cor[euler[l]]]++;
    if(occ[cor[euler[l]]]==1)resp++;
  }
  else{
    occ[cor[euler[l]]]--;
    if(occ[cor[euler[l]]]==0)resp--;
  }
  

}
 
void walkLRight(){//removing l;

  quem[euler[l]]--;
  if(quem[euler[l]]&1){
    occ[cor[euler[l]]]++;
    if(occ[cor[euler[l]]]==1)resp++;
  }
  else {
    occ[cor[euler[l]]]--;
    if(occ[cor[euler[l]]]==0)resp--;
  }
  l++;
}



const int maxlog=20;
int dp[MAXN][maxlog];
int ddepth[MAXN];
void dfs(int u,int p,int d=0){
  beg[u]=sz(euler);
  euler.PB(u);
  ddepth[u]=d;
  dp[u][0]=p;
  for(int i=1;i<maxlog;i++)dp[u][i]=dp[dp[u][i-1]][i-1];
  for(auto k:grafo[u]){
    if (k!=p){
      dfs(k,u,d+1);
    }
  }
  en[u]=sz(euler);
  euler.PB(u);
}

int jmp(int a,int j){
  for (int i=0;i<maxlog;i++) if ((j>>i) & 1) {
    a=dp[a][i];
  }
  return a;
}

int lca(int a,int b){

  if (ddepth[a]>ddepth[b]) swap(a,b);
  b=jmp(b,ddepth[b]-ddepth[a]);
  if (a==b) return a;

  for (int i=maxlog-1;i>=0;i--){
    if (dp[a][i]!=dp[b][i]){
      a=dp[a][i];
      b=dp[b][i];
    }
  }
  return dp[a][0];
}
/*
 MO on tree to get how many distinct on a path from u to v;
 To query from u to v is the same as a range query from en[u] to beg[v];
 Just check how many of the nodes on the euler tour only appear once, and get how many distinct between them
 Plus, just add the lca manually,as it will not be included in the range query;
*/
 
signed main(){
  iostream::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin>>n>>q;
  FOR(i,n)cin>>cor[i+1];
  FOR(i,n-1){
    int a,b;cin>>a>>b;
    grafo[a].PB(b);
    grafo[b].PB(a);
  }
  dfs(1,0);
  
  
  vector<Query> qs(q);
  VPII gamb(q);
  for(int i = 0; i < q; ++i){
    int a,b;
    cin >> a >> b;
    if (en[a]>beg[b])swap(a,b);
    qs[i].l=en[a];
    qs[i].r=beg[b];
    gamb[i]={a,b};
    qs[i].idx = i;
    qs[i].calcOrder();
  }
  sort(qs.begin(), qs.end(), [&](Query &a, Query &b){return a.ord < b.ord;});
  vector<int> ans(q);
  //print(euler);
  for(auto q : qs){
    //deb(q.l,q.r);
    // first expand range
    while(r < q.r) walkRRight();
    while(l > q.l) walkLLeft();
    // then restrict
    while(r > q.r) walkRLeft();
    while(l < q.l) walkLRight();
    
    ans[q.idx] = resp;
    int a,b;
    tie(a,b)=gamb[q.idx];
    //deb(cor[lca(a,b)]);
    //deb(resp,occ[cor[lca(a,b)]]);
    if (occ[cor[lca(a,b)]]==0)ans[q.idx]++;
  }
  for(auto x : ans) cout << x << "\n";
}
