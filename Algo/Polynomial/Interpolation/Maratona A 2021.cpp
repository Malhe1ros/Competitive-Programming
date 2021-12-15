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
	FOR(i,sz(v)){
		cout<<v[i];
		if(i+1!=sz(v))cout<<", ";
	}
	cout<<"]"<<endl;
}

void print(pii p){
	cout<<"{"<<p.first<<", "<<p.second<<"}"<<endl;
}

//solves https://codeforces.com/problemset/problem/622/F

//Done in O(N) (logN with inverses but optimizable);
 
const int MOD=1e9+7;

ll power(ll x, ll y) {
    ll ans = 1;
    x %= MOD;
    while (y > 0) {
        if (y%2==1) ans = (ans*x)%MOD;
        y /= 2;
        x = (x*x)%MOD;
    }
    return ans;
}
 
ll invMod(ll a){
  return power(a,MOD-2);
}

//assumes x={0,1,2,3,...,n}
//it is easy to change range to {x,x+1,...,x+n};

bool isprecalced=0;
const int maxn=1e6+10;
int fat[maxn];
int invfat[maxn];
void precalc(){
  isprecalced=1;
  fat[0]=1;
  
  for(int i=1;i<maxn;i++)fat[i]=(i*fat[i-1])%MOD;
  invfat[maxn-1] = power(fat[maxn-1],MOD-2);
  for (int i = maxn-2; i >= 0; i--) {
      invfat[i] = (invfat[i+1]*(i+1))%MOD;
  }
}
int interpolate(vector<int>& y,int u){
  if(!isprecalced)precalc();
  int n=y.size();
  vector<int> suf(n+1,1);
  for(int i=n-1;i>=0;i--) suf[i]=(suf[i+1]*(u-i))%MOD;
  int pref=1;
  int ans=0;
  for(int i=0;i<n;i++){
    int num=(pref*suf[i+1])%MOD;
    int den=(invfat[i]*invfat[n-1-i])%MOD;

    
    int toad=(y[i]*num)%MOD;
    toad*=den;
    toad%=MOD;
    if((n-1-i)%2)toad*=-1;
    ans+=toad;
    ans%=MOD;
    pref*=(u-i);
    pref%=MOD;
  }
  return ans;
  
}
 
 

signed main(){
  GO FAST
  int n,r;cin>>n>>r;
  VI l(n);
  FOR(i,n)cin>>l[i];
  for(int i=n-2;i>=0;i--){
    l[i]=max(l[i+1],l[i]);
  }
  if(*max_element(all(l))>r){
    cout<<0<<'\n';
    return 0;
  }

  VI pol={1-l.back(),2-l.back()};
  for(int i=n-2;i>=0;i--){
    pol.PB(interpolate(pol,sz(pol)));
    for(int j=1;j<sz(pol);j++){
      pol[j]+=pol[j-1];
      pol[j]%=MOD;
    }
    auto x=interpolate(pol,l[i]-1);
    for(auto &k:pol)k=(k-x)%MOD;
  }

  cout<<(interpolate(pol,r)+MOD)%MOD<<'\n';
}
