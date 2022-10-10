#include <bits/stdc++.h>
 

using namespace std;

#define int long long
#define ll long long

const int maxn = 3e5+10;
int arr[maxn];
struct fenwick{

    int size = maxn;
    fenwick(){

    }

    void update(int i,int delta){
        for (;i<size;i += i&(-i))arr[i]+=delta;
    }
    ll query(int i){
        ll soma=0;
        for (;i;i-= i &(-i))soma+=arr[i];
        return soma;
    }

};


 
struct Query{
  int l;
  int r;
  int soma;
  Query(){

  }
  Query(int a,int b,int c){
    l = a;
    r = b;
    soma = c;
  }
};

int ans[maxn];
fenwick seg;

vector<int> dono;
vector<int> pontosInteresse[maxn];
int preciso[maxn];
int prefixo = -1;
vector<Query> allQueries;

int n;
void applyQuery(int l,int r,int v){
  if(l>r){
    applyQuery(0,r,v);
    applyQuery(l,n-1,v);
  }
  else{
    seg.update(l+1,v);
    seg.update(r+2,-v);
  }

}

void solve(int l,int r,vector<int> interesseRange){
  
  if(interesseRange.empty())return; //pruning

  int mid = (l+r)/2;

  for(int i = l ; i <= mid ; ++i){ //adding all necessary;
    applyQuery(allQueries[i].l,allQueries[i].r,allQueries[i].soma);
  }

  vector<int> left;
  vector<int> right;
  for(auto k:interesseRange){//query for all and separate in left and right
    unsigned long long tot = 0;
    for(auto ponto:pontosInteresse[k]){
      tot+=seg.query(ponto+1);
    }
    if(tot>=preciso[k]){
      left.push_back(k);
      ans[k] = min(ans[k],mid);
    }
    else{
      right.push_back(k);
    }
  }
  
    if(r-l>1)solve(mid+1,r,right);// go to right without removing

    for(int i = l ; i <= mid ; ++i){//removing all necessary;
      applyQuery(allQueries[i].l,allQueries[i].r,-allQueries[i].soma);
    }

    if(r-l>1)solve(l,mid,left);
}

signed main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  for(int i=0;i<maxn;i++)ans[i] = INT_MAX;
  int m;cin>>m>>n;

  dono = vector<int>(n);
  
  for(int i=0;i<n;i++){
    int x;cin>>x;x--;
    pontosInteresse[x].push_back(i);
  }
  vector<int> interesseAtual(m);
  for(int i=0;i<m;i++){
    cin>>preciso[i];
    interesseAtual[i]=i;
  }

  int q;cin>>q;

  
  
  for(int i=0;i<q;i++){
    int l,r,val;cin>>l>>r>>val;l--;r--;
    allQueries.push_back(Query(l,r,val));
  }

  solve(0,q,interesseAtual);
  for(int i = 0;i<m;i++){
    if(ans[i]==INT_MAX) cout<<"NIE\n";
    else cout<<ans[i]+1<<"\n";
  }
}
