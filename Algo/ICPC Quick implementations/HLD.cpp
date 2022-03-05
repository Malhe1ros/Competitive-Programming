#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define int long long
struct segtree{
  int* arr;
  int* lazy;
  int size;
  int neutro;
  int lneutro;
 
  int op(int a,int b){
    return a+b;
  }
 
  int lazyop(int a,int b){
    return a+b;
  }

  segtree(){

  }
 
  segtree(vector<int>&v,int neut,int lazyneut){
    neutro=neut;
    lneutro=lazyneut;
    int n=v.size();
    size=1;
    while(size<n){
      size*=2;
    }
    arr = new int[2*size];
    lazy = new int[2*size];
    for (int i=0;i<2*size;i++){
      lazy[i]=lneutro;
      arr[i]=neutro;
    }
    build(v,0,0,size);
  }
  void build(vector<int>&v,int x,int l,int r){
    if (r-l==1){
      if (l<v.size()){
        arr[x]=v[l];
      }
      return;
    }
    int mid = l + (r-l)/2;
    build(v,2*x+1,l,mid);
    build(v,2*x+2,mid,r);
    arr[x]=op(arr[2*x+1],arr[2*x+2]);
  }
  
  void propagate(int x,int l,int r){
    arr[x]=lazyop(lazy[x],arr[x]);
    if(r-l==1){      
      lazy[x]=lneutro;
      return;
    }
    lazy[2*x+1]=lazyop(lazy[x],lazy[2*x+1]);
    lazy[2*x+2]=lazyop(lazy[x],lazy[2*x+2]);
    lazy[x]=lneutro;
  }
 
  void update(int v,int l,int r,int x,int lx,int rx){
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
  void update(int l,int r,int v){
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

const int MAX=5e5+10;
//MUDAR SEG INCLUSA;
namespace HLD {
	vector<int> g[MAX];
	int pos[MAX], sz[MAX];
	int peso[MAX], pai[MAX];
	int h[MAX], v[MAX], t;
	segtree seg;
	void setpeso(int a,int b){
		peso[a]=b;
	}
	void addEdge(int a,int b){
		g[a].push_back(b);
		g[b].push_back(a);
	}
	void build_hld(int k, int p = -1, int f = 1) {
		v[pos[k] = t++] = peso[k]; sz[k] = 1;
		for (auto& i : g[k]) if (i != p) {
			pai[i] = k;
			h[i] = (i == g[k][0] ? h[k] : i);
			build_hld(i, k, f); sz[k] += sz[i];

			if (sz[i] > sz[g[k][0]] or g[k][0] == p) swap(i, g[k][0]);
		}
		if (p*f == -1) build_hld(h[k] = k, -1, t = 0);
	}
	void build(int root = 0) {
		t = 0;
		build_hld(root);
		vector<int> segc(t);
		for(int i=0;i<t;i++){
			segc[i]=v[i];
		}
		seg=segtree(segc,0,0);
	}
	ll query_path(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return seg.query(pos[b], pos[a]+1);
		return seg.query(pos[h[a]], pos[a]+1) + query_path(pai[h[a]], b);
	}
	void update_path(int a, int b, int x) {
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return (void)seg.update(pos[b], pos[a]+1, x);
		seg.update(pos[h[a]], pos[a]+1, x); update_path(pai[h[a]], b, x);
	}
	ll query_subtree(int a) {
		return seg.query(pos[a], pos[a]+sz[a]-1);
	}
	void update_subtree(int a, int x) {
		seg.update(pos[a], pos[a]+sz[a], x);
	}
	int lca(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
}

signed main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int n,m;cin>>n>>m;
	vector<int>v(n);
	for(int i=0;i<n;i++){
		cin>>v[i];
		HLD::setpeso(i,v[i]);
	}
	
	for(int i=0;i<n-1;i++){
		int a,b;cin>>a>>b;
		HLD::addEdge(a,b);
	}
	HLD::build(0);
	while(m--){
		int a,b,c;cin>>a>>b>>c;
		if(a==0){
			HLD::update_path(b,b,c);
		}
		else{
			cout<<HLD::query_path(b,c)<<'\n';
		}
	}

}
