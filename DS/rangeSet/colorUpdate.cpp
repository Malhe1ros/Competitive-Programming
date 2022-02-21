#include <bits/stdc++.h>
 
using namespace std;

struct colorUpdate{
  set<pair<int,int>> ranges;
  map<pair<int,int>,int> cor;
  colorUpdate(int n){
    ranges.insert({1,n});
    cor[{1,n}]=1;
  }
  void bota(int lx,int rx,int c){
    ranges.insert({lx,rx});
    cor[{lx,rx}]=c;
  }
  void tira(int lx,int rx,int l,int r){//vou tirar o range [lx,rx] pra colocar [l,r];
    int corant=cor[{lx,rx}];
    ranges.erase({lx,rx});
    cor.erase({lx,rx});
    if(l<=lx && rx<=r){
      return;
    }
    if(lx<l){
      if(l-1>=lx){
        bota(lx,l-1,corant);
      }
    }
    if(rx>r){
      if(r+1<=rx){
        bota(r+1,rx,corant);
      }
    }
  }

  void insert(int l,int r,int c){
    auto prim=ranges.lower_bound({l,-1});
    if(prim==ranges.end()){
      prim--;
    }
    else if(prim->first>l)prim--;
    //agora tenho prim->first<l;
    vector<pair<int,int>> caras;//tem todos os ranges que me intersectam;
    while(prim!=ranges.end()){
      if(prim->first>r)break;
      caras.push_back(*prim);
      prim++;
    }
    for(auto k:caras){
      tira(k.first,k.second,l,r);
    }
    bota(l,r,c);
  }
  int find(int x){
    auto prim=ranges.lower_bound({x,-1});
    if(prim!=ranges.end()){
      if(prim->first==x)return cor[*prim];
    }
    prim--;
    return cor[*prim];
  }
  /*
  void print(){
    for(auto k:cor){
      cout<<"{"<<k.first.first<<" "<<k.first.second<<"} = "<<k.second<<endl;
    }
    cout<<"____________________-\n";
    for(auto k:ranges){
      cout<<k.first<<" "<<k.second<<endl;
    }
    cout<<"___________________-\n";
  }*/
};



signed main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n,q;cin>>n>>q;
  colorUpdate cu(n);
  
}
