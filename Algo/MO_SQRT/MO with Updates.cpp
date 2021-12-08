#include <bits/stdc++.h>
 
using namespace std;
/*
  MO's algorithm with updates;
  Runs in O(N^(5/3));
  Set block size to (2*maxn)^(2/3) to run optimally;
*/

#define sz(x) (int)x.size()
int l=0;
int r=-1;
int u=-1;
vector<pair<int,int>> updates;
vector<pair<pair<int,int>,pair<int,int>>> queries;
vector<int>v;
const int maxn=3e5+10;//maxn is actually 1e5;
const int magic=2200; //(2*maxn)^(2/3)
int cont[maxn];
int howmany[maxn];

//sort first by left BLOCK, then by right BLOCK, then by time;
bool cmp(const pair<pair<int,int>,pair<int,int>>&a,const pair<pair<int,int>,pair<int,int>>&b){
  if ((a.first.first/magic) == (b.first.first/magic)){
    if ((a.first.second/magic) == (b.first.second/magic)){
      return a.second.first<b.second.first;
    }
    return (a.first.second/magic) < (b.first.second/magic);
  }
  return (a.first.first/magic) < (b.first.first/magic);
}

void add(int x){//adds index x;
  howmany[cont[v[x]]]--;
  cont[v[x]]++;
  howmany[cont[v[x]]]++;
}

void rem(int x){//removes index x; 
  howmany[cont[v[x]]]--;
  cont[v[x]]--;
  howmany[cont[v[x]]]++;
}

stack<pair<int,int>> ups;
void updt(int x){//makes update x;
  if (updates[x].first>=l && updates[x].first<=r){
    howmany[cont[v[updates[x].first]]]--;
    cont[v[updates[x].first]]--;
    howmany[cont[v[updates[x].first]]]++;

    ups.push({updates[x].first,v[updates[x].first]});
    v[updates[x].first]=updates[x].second;

    howmany[cont[v[updates[x].first]]]--;
    cont[v[updates[x].first]]++;
    howmany[cont[v[updates[x].first]]]++;
  }
  else{
    ups.push({updates[x].first,v[updates[x].first]});
    v[updates[x].first]=updates[x].second;
  }
}

void rollback(){//removes last update;
  auto o=ups.top();
  ups.pop();
  if(o.first>=l && o.first<=r){
  howmany[cont[v[o.first]]]--;
  cont[v[o.first]]--;
  howmany[cont[v[o.first]]]++;
  
  v[o.first]=o.second;
 
  howmany[cont[v[o.first]]]--;
  cont[v[o.first]]++;
  howmany[cont[v[o.first]]]++;
  }
  else v[o.first]=o.second;
}

int query(){//queries;
  int i=0;
  while(howmany[i]!=0)i++;
  return i;
}

int ans[maxn];
map<int,int> mapa;

signed main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  howmany[0]=2e5;
  int n,q;cin>>n>>q;
  v=vector<int>(n);
  int cont=1;
  for(int i=0;i<n;i++){
    int a;
    cin>>a;
    if(mapa.find(a)==mapa.end())mapa[a]=cont++;
    v[i]=mapa[a];
  }
  for(int i=0;i<q;i++){
    int a,b,c;
    cin>>a>>b>>c;
    if(a==1){//findmex
      b--;c--;
      auto id=sz(queries);
      queries.push_back({{b,c},{sz(updates)-1,id}});//query from b to c
    }
    else{//update
      b--;
      if (mapa.find(c)==mapa.end())mapa[c]=cont++;
      updates.push_back({b,mapa[c]});//updating b to c;
    }
  }

  sort(queries.begin(),queries.end(),cmp);
  int esq,dir,tempo,id;
  for(auto k:queries){
    tie(esq,dir,tempo,id)={k.first.first,k.first.second,k.second.first,k.second.second};
    while(esq<l){
      l--;
      add(l);
    }
    while(dir>r){
      r++;
      add(r);
    }
    while(esq>l){
      rem(l);
      l++;
    }
    while(dir<r){
      rem(r);
      r--;
    }
    
    while(tempo>u){
      u++;
      updt(u);
    }
    while(tempo<u){
      rollback();
      u--;
    }
    ans[id]=query();
  }
  for(int i=0;i<sz(queries);i++){
    cout<<ans[i]<<'\n';
  }
}
