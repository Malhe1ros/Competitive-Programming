
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

template<class nd>
struct segtree{
    vector<nd> seg;
    nd merge(nd a,nd b){
		return max(a,b);
	}
    int size;
    nd neutro;
    segtree(){
      
    }
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
    tree=segtree<ll>(v,0);   
	}

  //lowest common ancestor because you may need
	int lca(int x, int y) {
		for (; root[x] != root[y]; y = par[root[y]])
			if (ddepth[root[x]] > ddepth[root[y]]) swap(x,y);
		return ddepth[x] < ddepth[y] ? x : y;
	}
	segtree<ll> tree;//my segtree

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

	void modifyNode(int x, int v) { 
      tree.set(pos[x],v);
    }
	
  ll queryPath(int x, int y) { 
    if(root[x]==root[y]){
      if(pos[x]>pos[y])swap(x,y);
      
      return tree.query(pos[x],pos[y]+1);
    }
    if(ddepth[root[x]]<ddepth[root[y]]) swap(x,y);
    int a=x;
    int b=root[x];
    if(pos[a]>pos[b])swap(a,b);
    return tree.merge(queryPath(par[root[x]],y),tree.query(pos[a],pos[b]+1));

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
            hld.modifyNode(b,c);
        }
        else{
            b--;c--;
            cout<<hld.queryPath(b,c)<<" ";
        }
        

    }

  cout<<endl;    
}
