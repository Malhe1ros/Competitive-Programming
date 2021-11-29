#include <bits/stdc++.h>
 
using namespace std;

//solves https://codeforces.com/contest/1609/problem/E
 
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

struct nd{
	int a,b,c,ab,bc,abc;
	nd(char C){
		a=b=c=ab=bc=abc=0;
    if (C=='a'){
      a=1;
    }
    else if (C=='b'){
      b=1;
    }
    else{
      c=1;
    }
	}
	nd(){
    a=b=c=ab=bc=abc=0;
	}
};

template<class nd>
struct segtree{
    vector<nd> seg;
    nd merge(nd A,nd B){
      //deb(A.a,A.b,A.c,A.ab,A.bc,A.abc);
      nd novo;
      novo.a=A.a+B.a;
      novo.b=A.b+B.b;
      novo.c=A.c+B.c;
      novo.ab=min(A.a+B.ab,A.ab+B.b);
      novo.bc=min(A.b+B.bc,A.bc+B.c);
      novo.abc=min({A.a+B.abc,A.ab+B.bc,A.abc+B.c});
      return novo;
	  }
    int size;
    nd neutro;
    segtree(vector<nd>&v,nd neu){
        int n=1;
        while(n<v.size()) n=n<<1;
        seg.assign(2*n,neu);

        size=n;
        neutro=neu;
        build(v,0,0,size);
    }
    void build(vector<nd>& v,int x,int lx,int rx){
        if (rx-lx==1){
            if (lx<v.size()) seg[x]=v[lx];
            return;
        }
        int mid = lx + (rx-lx)/2;
        build(v,2*x+1,lx,mid);
        build(v,2*x+2,mid,rx);
        seg[x]=merge(seg[2*x+1],seg[2*x+2]);
    }
    
    void set(int index,nd valor,int x,int lx,int rx){
        if(rx-lx==1){
            seg[x]=valor;
            return;
        }
        int mid=lx+(rx-lx)/2;
        if (index<mid){
            set(index,valor,2*x+1,lx,mid);
        }
        else{
            set(index,valor,2*x+2,mid,rx);
        }
        seg[x]=merge(seg[2*x+1],seg[2*x+2]);
    }


    void set(int index,nd valor){
        set(index,valor,0,0,size);
    }

    nd query(int l,int r,int x,int lx,int rx){
        if (r<=lx || l>=rx) return neutro;
        if (lx>=l && rx<=r) return seg[x];
        int mid = lx+(rx-lx)/2;
        return merge(query(l,r,2*x+1,lx,mid),query(l,r,2*x+2,mid,rx));
    }
    
    
    
    nd query(int l,int r){
        return query(l,r,0,0,size);
    }

};

signed main(){
  GO FAST
  int n,t;cin>>n>>t;
  string s;cin>>s;
  vector<nd> v(n);
  char C='a';
  nd neu(C);
  neu.a--;

  FOR(i,n){
    v[i]=nd(s[i]);
  }
  segtree<nd> seg(v,neu);
  while(t--){
    int a;char c;cin>>a>>c;
    a--;
    seg.set(a,nd(c));
    cout<<seg.seg[0].abc<<'\n';
  }
}
