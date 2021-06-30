#include <bits/stdc++.h>
#define int long long
using namespace std;
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
    arr[x]=arr[x]+lazy[x]*(r-l);
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
      lazy[x]=lazyop(lazy[x],v);
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
 
int32_t main(){
  long long n,m;scanf("%lld %lld",&n,&m);
  vector<long long> v(n,0);
  segtree s= segtree(v,0,0);
  while(m--){
      long long a;scanf("%lld",&a);
      if (a==1){
          long long b,c,d;
          scanf("%lld %lld %lld",&b,&c,&d);
        s.update(b,c,d);
      }
      else{
          long long b,c;
          scanf("%lld %lld",&b,&c);
          printf("%lld\n",s.query(b,c));
      }
          
  }
 
}
