#include <bits/stdc++.h>

using namespace std;

#define ld long double
#define ll long long
#define int long long
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

struct node{
  int val;
  int l,r;
  node(){
    val=0;
    l=-1;
    r=-1;
  }
  node(int a,int b,int c){
    val=a;
    l=b;
    r=c;
  }
};

/*
    Fully persistent segment tree
    Like a normal segment tree but you can query its state at any time t;
*/

template<int MAXN>
struct persistentSegtree{
  node segtree[64*MAXN];//array to store segtree
  int tempos[MAXN];//array to store the index of the parent at time t;
  int tempoatual=0;//position i will add the next time
  int neutro;//neutral element of op
  int size;//size of my maximum range;
  int atual=0;//position i will add the next node;
  int op(int a,int b){
    return a+b;
  }
  persistentSegtree(vector<int>&v,int n=0){
    neutro=n;
    int ss=v.size();
    size=1;
    while(size<ss){
      size<<=1;
    }
    tempos[tempoatual++]=build(v,0,size);
  }
  int build(vector<int>&v,int lx,int rx){
    if (rx-lx==1){
      if (lx<v.size())segtree[atual]=node(v[lx],-1,-1);
      return atual++;
    }
    int mid = (lx+rx)/2;
    int esq=build(v,lx,mid);
    int dir=build(v,mid,rx);
    segtree[atual]=node(op(segtree[esq].val,segtree[dir].val),esq,dir);
    return atual++;
  }

  int query(int ind,int searchL,int searchR,int lx,int rx){
    if (searchL>=lx && searchR<=rx)return segtree[ind].val;
    if (searchR<=lx || searchL>=rx)return neutro;
    int mid=(searchL+searchR)/2;
    return op(query(segtree[ind].l,searchL,mid,lx,rx),query(segtree[ind].r,mid,searchR,lx,rx));
  }

  //used to query current state;
  int query(int lx,int rx){
    return query(tempoatual-1,lx,rx);
  }
  
  //used to query past state
  int query(int t,int lx,int rx){
    assert(t<tempoatual);
    return query(tempos[t],0,size,lx,rx);
  }

  //update current state
  void update(int ind,int v){
    update(tempoatual-1,ind,v);
  }
  
  //update past state
  void update(int t,int i,int v){
    update(tempos[t],0,size,i,v);
    tempos[tempoatual++]=atual-1;
  }
  void update(int ind,int searchL,int searchR,int i,int v){
    if (searchR-searchL==1){
      segtree[atual++]=node(v,-1,-1);
      return;
    }
    int mid=(searchL+searchR)/2;
    if (i<mid){
      update(segtree[ind].l,searchL,mid,i,v);
      int filhodir=segtree[ind].r;
      int filhoesq=atual-1;
      segtree[atual++]=node(op(segtree[filhoesq].val,segtree[filhodir].val),filhoesq,filhodir);
    }
    else{
      update(segtree[ind].r,mid,searchR,i,v);
      int filhoesq=segtree[ind].l;
      int filhodir=atual-1;
      segtree[atual++]=node(op(segtree[filhoesq].val,segtree[filhodir].val),filhoesq,filhodir);
    }
  }

	int kth(int esqnode,int dirnode,int k,int lx,int rx){
		if (rx-lx==1)return lx;
		int mid=lx+(rx-lx)/2;
		int qesq=segtree[segtree[esqnode].l].val;
		int qdir=segtree[segtree[dirnode].l].val;
		int total=qdir-qesq;
		if (total>=k){
			return kth(segtree[esqnode].l,segtree[dirnode].l,k,lx,mid);
		}
		else{
			return kth(segtree[esqnode].r,segtree[dirnode].r,k-total,mid,rx);
		}
	}

  int kth(int esq,int dir,int k){
	  esq--;
	  auto segl=tempos[esq];
	  auto segr=tempos[dir];
	  return kth(segl,segr,k,0,size);
  }

  //function to print the segment tree at time t;
  void print(int t){
    queue<int>indexes;
    indexes.push(tempos[t]);
    while(!indexes.empty()){
      auto o=indexes.front();
      indexes.pop();
      cout<<segtree[o].val<<" ";
      if (segtree[o].l!=-1)indexes.push(segtree[o].l);
      if (segtree[o].r!=-1)indexes.push(segtree[o].r);
    }
  cout<<endl;

  }
};

const int maxn=200010;
VI v(maxn,0);
persistentSegtree<maxn> arv(v);
signed main(){
	GO FAST
	int n,q;cin>>n>>q;
	VI v(n);
	
	FOR(i,n)cin>>v[i];
	VI vals=v;
	sort(all(vals));
	map<int,int> mapa;
	VI caras;
	int cont=0;
	for (auto k:vals){
		if (mapa.find(k)==mapa.end()){
			caras.push_back(k);
			mapa[k]=cont++;
		}
	}
	FOR(i,n) v[i]=mapa[v[i]];
	VI tot(maxn);
	FOR(i,n){
		arv.update(v[i],++tot[v[i]]);
	}
	//print(caras);
	//00000 0
	//00001 1 
	while(q--){
		int a,b,c;cin>>a>>b>>c;a++;c++;
		cout<<caras[arv.kth(a,b,c)]<<'\n';
	}
}
