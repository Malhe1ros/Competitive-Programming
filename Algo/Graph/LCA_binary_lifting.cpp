#include <bits/stdc++.h>

/*
  IDK WHY MY CODE GOT SO UGLY BUT YEAH, IT CALCULATES LCA QUERIES IN O(logN) with O(N*logN) preprocessing
  solves: https://cses.fi/problemset/task/1688/
*/

using namespace std;

const int maxn=2e5+10;
const int maxlog=31;

int dp[maxn][maxlog]

//quem eh o j ancestral de a em O(logN)
int jmp(int a,int j){
  // dou um bit shift de i, se eu tenho que subir 2^i eu subo 2^i;
  for (int i=0;i<maxlog;i++) if ((j>>i) & 1) {
    a=dp[a][i];
  }
  return a;
}
vector<int> grafo[maxn];
int cont=0;
int ddepth[maxn];
void dfs(int i=1,int cont=0){
  ddepth[i]=cont;
  for (auto k:grafo[i]) dfs(k,cont+1);
}

int lca(int a,int b){
  if (ddepth[a]>ddepth[b]) swap(a,b);
  b=jmp(b,ddepth[b]-ddepth[a]);
  if (a==b) return a;
  for (int i=maxlog-1;i>=0;i--){
    if (dp[a][i]!=dp[b][i]){
      a=dp[a][i];
      b=dp[b][i];
    }
  }
  return dp[a][0];
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  int n,q;
  cin>>n>>q;
  for (int i=2;i<=n;i++){
    int a;cin>>a;
    dp[i][0]=a;
    grafo[a].push_back(i);
  }
  dfs();  
    for (int j=1;j<maxlog;j++) 
    for (int i=1;i<=n;i++) 
      //No ponto i, subindo 2^j é igual a (no ponto i subindo 2^(j-1)) subindo 2^(j-1);    
      dp[i][j]=dp[dp[i][j-1]][j-1];

  while(q--){
    int a,b;cin>>a>>b;
    cout<<lca(a,b)<<"\n";
  }
}
