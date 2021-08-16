#include <bits/stdc++.h>
#define int long long
using namespace std;
 
struct nd{
	int pref;
  int suf;
  int ins;
  int tot;
  
	nd(int a){
    tot=a;
    a=max(a,0ll);
		pref=a;
    suf=a;
    ins=a;
	}
	nd(){
	}
};
const int neut=2e16;
 
template <class nd>
struct segtree{
  nd* arr;//real information
  nd* lazy;//lazy information
  int size;//size of my segtree
  nd neutro;//neutral element of op operation
  nd lneutro;//neutral element of lazy operation
 
  /*
    apply operation on a and b
    watch out, it is copying a and b everytime, sometimes you need to optimize;
  */
  nd op(nd a,nd b){
    nd novo;
    novo.pref=max(b.pref+a.tot,a.pref);
    novo.suf=max(b.suf,a.suf+b.tot);
    novo.ins=max(max(a.ins,b.ins),a.suf+b.pref);
    novo.tot=a.tot+b.tot;
    return novo;
  }
 
  /*
    push lazy from node[inda] to node[indb];
  */
  void pushlazy(int inda,int indb){
    if (lazy[inda].tot==neut){
      return;
    }
    lazy[indb] = lazy[inda];
  }
 
 
  /*
    apply lazy operation located at ind;
  */
  void applylazyatnode(int ind,int nodesize){
    if (lazy[ind].tot==neut){
      return ;
    }
    if (lazy[ind].tot<0){
      nd b(0);
      b.tot=nodesize*lazy[ind].tot;
      arr[ind] = b;
      return;
    }
    int toadd=nodesize*lazy[ind].tot;
    arr[ind].pref=toadd;
    arr[ind].suf=toadd;
    arr[ind].ins=toadd;
    arr[ind].tot=toadd;
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
    applylazyatnode(x,r-l);
    if(r-l==1){      
      lazy[x]=lneutro;
      return;
    }
    pushlazy(x,2*x+1);
    pushlazy(x,2*x+2);
    lazy[x]=lneutro;
  }
 
  void update(nd& v,int l,int r,int x,int lx,int rx){
    propagate(x,lx,rx);
    if (lx>=r || rx<=l)return;
    if (lx>=l && rx<=r){
      lazy[x]=v;
      propagate(x,lx,rx);
      return;
    }
    int mid = lx + (rx-lx)/2;
    update(v,l,r,2*x+1,lx,mid);
    update(v,l,r,2*x+2,mid,rx);
    arr[x]=op(arr[2*x+1],arr[2*x+2]);
  }
 
  void update(int l,int r,nd& v){
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
 
int32_t main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n,m;cin>>n>>m;
  vector<nd> v(n,nd(0));
  nd neuop(0);
  nd neulazyop(neut);
  segtree<nd> s= segtree<nd>(v,neuop,neulazyop);
  while(m--){
      int a,b,c;cin>>a>>b>>c;
      nd gg=nd(c);
      s.update(a,b,gg);
      cout<<s.query(0,n).ins<<'\n';
  }
 
}
