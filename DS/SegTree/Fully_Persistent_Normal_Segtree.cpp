#include <bits/stdc++.h>
 
using namespace std;
 #define int long long

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
  node segtree[64*MAXN];//array to store segtree 25*MAXN works well for 3e5
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


const int maxn=2e5+10;
int pontok[maxn];
int32_t main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n,q;cin>>n>>q;
  vector<int>v(n);
  for (auto&k:v)cin>>k;
  persistentSegtree<maxn> ss(v);
  int contagemnovos=1;
  while(q--){
    int t;cin>>t;
    if (t==1){
      int k,a,x;//set array k at point a to value x;
      cin>>k>>a>>x;
      k--;
      a--;
      ss.update(pontok[k],a,x);
      pontok[k]=ss.tempoatual-1;
    }
    else if (t==2){
      int k,a,b;cin>>k>>a>>b;
      k--;
      cout<<ss.query(pontok[k],a-1,b)<<endl;
    }
    else{
      int k;cin>>k;k--;
      ss.update(pontok[k],0,ss.query(pontok[k],0,1));
      pontok[contagemnovos++]=ss.tempoatual-1;
    }
  }

}
