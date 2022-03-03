#include <bits/stdc++.h>
#define int long long
using namespace std;
 
struct nd{
  int beg;
  int step;
  
	nd(int a,int b){
    beg=a;
    step=b;
	}
	nd(){
    beg=0;
    step=0;
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
 
  int calc(nd& a,int tam){
    return (a.beg+a.step*(tam-1)+a.beg)*tam/2;
  }
  /*
    apply operation on a and b
    watch out, it is copying a and b everytime, sometimes you need to optimize;
  */
  nd op(nd a,nd b){
    return nd(a.beg+b.beg,0);
  }
 
  /*
    push lazy from node[inda] to node[indb];
  */
  void pushlazy(int inda,int indb){
    lazy[indb].beg+=lazy[inda].beg;
    lazy[indb].step+=lazy[inda].step;
  }
 
 
  /*
    apply lazy operation located at ind;
  */
  void applylazyatnode(int ind,int nodesize){
    arr[ind].beg+=calc(lazy[ind],nodesize);
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
    //build(v,0,0,size);
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
    //pushlazy(x,2*x+1);
    lazy[2*x+1].beg+=lazy[x].beg;
    lazy[2*x+1].step+=lazy[x].step;
    //pushlazy(x,2*x+2);
    lazy[2*x+2].beg+=lazy[x].beg+lazy[x].step*(r-l)/2;
    lazy[2*x+2].step+=lazy[x].step;
    lazy[x]=lneutro;
  }
 
  void update(nd v,int l,int r,int x,int lx,int rx){
    propagate(x,lx,rx);
    if (lx>=r || rx<=l)return;
    if (lx>=l && rx<=r){
      lazy[x]=nd(v.beg+(lx-l)*v.step,v.step);
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
 
  nd query(int l,int x,int lx,int rx){
    propagate(x,lx,rx);
    
    if (rx-lx==1) return arr[x];
    int mid = lx + (rx-lx)/2;
    if (l<mid){
      return query(l,2*x+1,lx,mid);
    }
    else return query(l,2*x+2,mid,rx);
 
  }
 
  int query(int l){
    return query(l,0,0,size).beg;
  }
 
};
 
 
signed main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n,m;cin>>n>>m;
  vector<nd> v(n,nd());
  segtree<nd> s(v,nd(),nd());
  while(m--){
    int t;cin>>t;
    if (t==1){
      int l,r,a,d;cin>>l>>r>>a>>d;l--;r--;
      s.update(l,r+1,nd(a,d));
    }
    else{
      int b;cin>>b;b--;
      cout<<s.query(b)<<'\n';
    }
    /*for (int i=0;i<16;i++){
      cout<<s.lazy[i].beg<<" "<<s.lazy[i].step<<'\n';
    }*/
  }
}
