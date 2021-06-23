
#include <bits/stdc++.h>

#define ll int 
using namespace std;

/*
  Heavy light decomposition on steroids;
  Uses a lazy propagation segment tree to update and query paths;
*/


struct n1d{
	int x;
	n1d(int a){
		x=a;
	}
	n1d(){

	}
};


//Normal lazy segtree, see other documentation (if exists)
template <class nd>
struct segtree{
  nd* arr;
  nd* lazy;
  int size;
  nd neutro;
  nd lneutro;
 
  nd op(nd a,nd b){
    return max(a,b);
  }
 
  nd lazyop(nd a,nd b){
    if (a==lneutro)return b;
    return a;
  }
  segtree(){
  }
  segtree(int sz,nd neut,nd lazyneut){
    neutro=neut;
    lneutro=lazyneut;
    int n=sz;
    size=1;
    while(size<n){
        size*=2;
    }
    arr = new nd[2*size];
    lazy = new nd[2*size];
    for (int i=0;i<2*size;i++){
        lazy[i]=lneutro;
        arr[i]=neutro;
    }
  }
  segtree(vector<nd>&v,nd neut,nd lazyneut){
    neutro=neut;
    lneutro=lazyneut;
    int n=v.size();
    size=1;
    while(size<n){
      size*=2;
    }
    arr = new nd[2*size];
    lazy = new nd[2*size];
    for (int i=0;i<2*size;i++){
      lazy[i]=lneutro;
      arr[i]=neutro;
    }
    build(v,0,0,size);
  }
  void build(vector<nd>&v,int x,int l,int r){
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
 
  void update(nd v,int l,int r,int x,int lx,int rx){
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
  void update(int l,int r,nd v){
    return update(v,l,r,0,0,size);
  }
 
  nd query(int l,int r,int x,int lx,int rx){
    propagate(x,lx,rx);
    if (lx>=r || rx<=l)return neutro;
    if (lx>=l && rx<=r){
      return arr[x];
    }
    int mid = lx + (rx-lx)/2;
    return op(query(l,r,2*x+1,lx,mid),query(l,r,2*x+2,mid,rx));
  }
 
  nd query(int l,int r){
    return query(l,r,0,0,size);
  }
 
};

const int SZ=2e5+10;//maxn


//HLD<size,is the value on edges?>
template<int SZ, bool VALS_IN_EDGES> struct HLD { 
	int N;//HLD size 
  vector<int> adj[SZ];//adjacency list
	int par[SZ];//par[i] has the parent of i;
  int root[SZ];//root[i] has the root of the path which contains i
  int ddepth[SZ];//ddepth[i] has the depth of i
  int sz[SZ];//sz[i] has the size of subtree rooted on i;
  int ti;//for the euler tour stuff;
	int pos[SZ];//pos in segtree
  vector<int> rpos; // rpos gambiarra;
  int heavy[SZ];//heavy[i] has the heavy child of node i 
	void addEdge(int x, int y) { adj[x].push_back(y), adj[y].push_back(x); }//adds edges from x to y

  //normal dfs, it works, don't bother
	void dfs(int u,int p) { 
		sz[u] = 1; 
    int maior=-1;
    int quem=-1;
    par[u]=p;
		for (auto k :adj[u]) {
      if(k==p)continue;
			 ddepth[k] = ddepth[u]+1;
			dfs(k,u); 
      sz[u] += sz[k];
			if (sz[k] > maior) {
        maior=sz[k];
        quem=k;
      }
		}
    heavy[u]=quem;
	}

  //hld dfs, it works, don't bother
	void dfsHld(int x,int rr) {
		pos[x] = ti++; rpos.push_back(x);
    root[x]=rr;
    if (heavy[x]==-1) return;
    dfsHld(heavy[x],rr);
		for(auto y:adj[x]) {
      if (y==heavy[x] || y==par[x])continue;
			dfsHld(y,y); 
      }
	}

  //initialize hld with values;
	void init(vector<int>& valor,int R=0) { 
    N = valor.size();   
    par[R]=-1;
    ddepth[R]=0;
    ti = 0; 
    dfs(R,-1);
      
		dfsHld(R,R); 
    vector<int>v(N);
    for(int i=0;i<N;i++){
      v[i]=valor[rpos[i]];
    }
    tree=segtree<ll>(v,0,0);   
	}

  //lowest common ancestor with black magic;
	int lca(int x, int y) {
		for (; root[x] != root[y]; y = par[root[y]])
			if (ddepth[root[x]] > ddepth[root[y]]) swap(x,y);
		return ddepth[x] < ddepth[y] ? x : y;
	}
	segtree<ll> tree;//my segtree

  //black magic of some sort
  //YOU HAVE TO ADD THE VALS_IN_EDGE STUFF PLEASE REMEMBER
  /*
	template <class BinaryOp>
	void processPath(int x, int y, BinaryOp op) {
		for (; root[x] != root[y]; y = par[root[y]]) {
			if (ddepth[root[x]] > ddepth[root[y]]) swap(x,y);
			op(pos[root[y]],pos[y]); }
		if (ddepth[x] > ddepth[y]) swap(x,y);
		op(pos[x]+VALS_IN_EDGES,pos[y]); 
	}*/

	void modifyPath(int x, int y, int v) { 
    if(root[x]==root[y]){
      if(pos[x]>pos[y])swap(x,y);
      tree.update(pos[x]+VALS_IN_EDGES,pos[y]+1,v);
      return;
    }
    if(ddepth[root[x]]<ddepth[root[y]]) swap(x,y);
    int a=x;
    int b=root[x];
    if(pos[a]>pos[b])swap(a,b);
    tree.update(pos[a],pos[b]+1,v);
    modifyPath(par[root[x]],y,v);
    }
	
  ll queryPath(int x, int y) { 
    if(root[x]==root[y]){
      if(pos[x]>pos[y])swap(x,y);
      
      return tree.query(pos[x]+VALS_IN_EDGES,pos[y]+1);
    }
    if(ddepth[root[x]]<ddepth[root[y]]) swap(x,y);
    int a=x;
    int b=root[x];
    if(pos[a]>pos[b])swap(a,b);
    return tree.op(queryPath(par[root[x]],y),tree.query(pos[a],pos[b]+1));

  }

	void modifySubtree(int x, int v) { 
		tree.update(pos[x]+VALS_IN_EDGES,pos[x]+sz[x],v); 
    }


   
};
int main(){
  
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);


    int n,q;cin>>n>>q;

    HLD<SZ,false> hld;
    vector<int>valor(n);
    for (int i=0;i<n;i++){
        cin>>valor[i];
    }
 

    for(int i=0;i<n-1;i++){
        int a,b;cin>>a>>b;
        a--;b--;
        hld.addEdge(a,b);
    }
    hld.init(valor,0);

    while(q--){
        int a,b,c;cin>>a>>b>>c;
        if (a==1){
            b--;
            hld.modifyPath(b,b,c);
        }
        else{
            b--;c--;
            cout<<hld.queryPath(b,c)<<" ";
        }
        

    }

  cout<<endl;    
}
