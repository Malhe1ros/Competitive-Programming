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

template<typename Container>
void print(Container beg){
    cout<<"[";
    for(auto k:beg){
        cout<<k<<" ";
    }
    cout<<"]"<<endl;
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

const int MOD=998244353;
struct segtree{
  int* arr;
  vector<pair<int,int>> lazy;
  int size;
  int neutro;
  pair<int,int> lneutro;
 
  int op(int a,int b){
    return max(a,b);
  }
 
  pii lazyop(pii cxd,pii axb){
    int a = (axb.first*cxd.first)%MOD;
    int b = (axb.second*cxd.first+cxd.second)%MOD;
    return MP(a,b);
  }
 
  segtree(vector<int>&v){
    neutro = 0;
    lneutro = {1,0};
    int n=v.size();
    size=1;
    while(size<n){
      size*=2;
    }
    arr = new int[2*size];
    lazy = vector<pair<int,int>>(2*size);
    for (int i=0;i<2*size;i++){
      lazy[i]=lneutro;
      arr[i]=0;
    }
    
  }
  
  
  void propagate(int x,int l,int r){
    arr[x]=(lazy[x].first*arr[x]+lazy[x].second)%MOD;
    if(r-l==1){      
      lazy[x]=lneutro;
      return;
    }
    lazy[2*x+1]=lazyop(lazy[x],lazy[2*x+1]);
    lazy[2*x+2]=lazyop(lazy[x],lazy[2*x+2]);
    lazy[x]=lneutro;
  }
 
  void update(pii v,int l,int r,int x,int lx,int rx){
    propagate(x,lx,rx);
    if (lx>=r || rx<=l)return;
    if (lx>=l && rx<=r){
      lazy[x]=lazyop(v,lazy[x]);
      propagate(x,lx,rx);
      return;
    }
    int mid = lx + (rx-lx)/2;
    update(v,l,r,2*x+1,lx,mid);
    update(v,l,r,2*x+2,mid,rx);
    arr[x]=op(arr[2*x+1],arr[2*x+2]);
  }
  void update(int l,int r,pii v){
    return update(v,l,r,0,0,size);
  }
 
  int query(int l,int r,int x,int lx,int rx){
    propagate(x,lx,rx);
    if (lx>=r || rx<=l)return neutro;
    if (lx>=l && rx<=r){
      return arr[x];
    }
    int mid = lx + (rx-lx)/2;
    return op(query(l,r,2*x+1,lx,mid),query(l,r,2*x+2,mid,rx));
  }
 
  int query(int l,int r){
    return query(l,r,0,0,size);
  }
 
};


const int maxn=3e5+10;
signed main(){
  GO FAST
  int t;cin>>t;
  VI v(maxn);
  segtree seg(v);
  int cont=1;
  FOR(i,t){
    int l,r;cin>>l>>r;r++;
    //deb(l,r);
    if(i==1)cont*=2;
    if(i>=2)cont=(cont*3)%MOD;
    //deb(cont);
    seg.update(0,maxn,MP(2,0));//MULTIPLY ALL BY 2;
    seg.update(l,r,MP(0,cont));
    

    //FOR(j,9)cout<<seg.query(j,j+1)<<' ';
    //cout<<'\n';
  }
  int tot=0;
  FOR(i,maxn)tot=(tot+seg.query(i,i+1))%MOD;
  cout<<tot<<'\n';
}
