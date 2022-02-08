#include <bits/stdc++.h>
 
using namespace std;
 
#define ld long double
#define ll long long
//#define int ll
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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<
int,
null_type,
greater_equal<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

const int maxn=1e5+10;
int ans[maxn];

bool cmp(const pair<pii,pii> & a,const pair<pii,pii>& b){
  return a.first.second>b.first.second;
}

void pega(vector<pair<pii,pii>>& l,vector<pair<pii,pii>>& r){
  sort(all(l),cmp);
  sort(all(r),cmp);
  
  int p0=0;
  ordered_set novo;
  FOR(i,sz(r)){
    while((p0 < sz(l)) && (l[p0].first.second>r[i].first.second)){
      novo.insert(l[p0].second.first);
      p0++;
    }
    
    ans[r[i].second.second]+=novo.order_of_key(r[i].second.first);
  }
}
vector<pair<pii,pii>> v;


void solve(int l,int r){
  if(r-l==1)return;
  auto m=(l+r)/2;
  if(m==-1)return;
  solve(l,m);
  solve(m,r);
  vector<pair<pii,pii>> v1;
  vector<pair<pii,pii>> v2;
  for(int i=l;i<m;i++){
    v1.PB(v[i]);
  }
  for(int i=m;i<r;i++){
    v2.PB(v[i]);
  }
  pega(v1,v2);
}

bool cmp2(const pair<pii,pii>& a,const pair<pii,pii>& b){
  if(a.first.first==b.first.first){
    if(a.first.second == b.first.second){
      return a.SF<b.SF;
    }
    return a.FS<b.FS;
  }
  return a.first.first>b.first.first;
}

signed main(){
  GO FAST

  int n;cin>>n;
  v=vector<pair<pii,pii>>(n);
  FOR(i,n){
    int a,b,c;cin>>a>>b>>c;
    v[i]=MP(MP(a,b),MP(c,i));
  }
  sort(all(v),cmp2);
  solve(0,n);
  FOR(i,n){
    cout<<ans[i]<<"\n";
  }
}
