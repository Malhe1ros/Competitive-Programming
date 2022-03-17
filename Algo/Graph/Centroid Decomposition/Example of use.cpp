 
  
#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
const int maxn=1e5+10;
vector<int> grafo[maxn];//graph
bool rm[maxn];//is removed?
int sub[maxn];//subtree size;
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}
 
 
int dfs(int u,int p=-1){//dfs to find sizes;
    sub[u]=1;
    for(auto k:grafo[u]){
        if (k!=p && !rm[k])sub[u]+=dfs(k,u);
    }
    return sub[u];
}
 
int get_centroid(int u,int size,int p=-1){
    for(auto k:grafo[u]){
        if (k!=p && !rm[k]){
            if (sub[k]*2 > size){//if there is a subtree with size greater than size/2 i can find a centroid there;
                return get_centroid(k,size,u);
            }
        }
    }
    return u;//if there is no such subtree, then i am a centroid;
}
 
int root=-1;
long long tot=0;
int quantos=0;
int total=0;
int dp[20];
int ddp[20];
int valor[maxn];
void roda(int u,int p,int xo){
  //deb(u);
  quantos++;
  //total++;
  xo^=valor[u];
  for(int i=0;i<20;i++){
    if(xo&(1<<i)){
      //deb(xo,i);
      ddp[i]++;
      //deb(ddp[i]);
    }
  }
 
    for(auto k:grafo[u]){
        if (k!=p && !rm[k]){
          roda(k,u,xo);
        }
    }
}
int decomposition(int u=0){//doesn't matter which beggining node, calculates the centroid decomposition of the tree;
    int centroid=get_centroid(u,dfs(u));
    if (root==-1)root=centroid;
    rm[centroid]=1;
    //cout<<centroid<<endl;
 
    for(auto k:grafo[centroid]){
      if(!rm[k]){
        roda(k,centroid,0);
        for(int i=0;i<20;i++){
          int val=(1<<i);
          int qligado=ddp[i];
          //deb(quantos,i,ddp[i]);
          int qdesligado=(quantos)-ddp[i];
          int atuall=dp[i];
          int atuald=(total)-atuall;
          //deb(qligado,qdesligado,atuall,atuald,val);
          if(val&valor[centroid]){
            tot+=(ll)atuald*qdesligado*val;
            tot+=(ll)atuall*qligado*val;
            tot+=(ll)qdesligado*val;
            /*tot+=(ll)dq[0]*q[0]*val;
            tot+=(ll)dq[1]*q[1]*val;
            tot+=(ll)dq[0]*val;*/
          }
          else{
            tot+=(ll)atuall*qdesligado*val;
            tot+=(ll)atuald*qligado*val;
            tot+=(ll)qligado*val;
            /*tot+=(ll)dq[0]*q[1]*val;
            tot+=(ll)dq[1]*q[0]*val;
            tot+=(ll)dq[1]*val;*/
          }
          dp[i]+=ddp[i];
          ddp[i]=0;
        }
        total+=quantos;
        quantos=0;
      }
    }    
    total=0;
    for(int i=0;i<20;i++)dp[i]=0;
    for(auto k:grafo[centroid]){
        if (!rm[k]){
            auto l1=decomposition(k);
        }
    }
    return centroid;
}
 
 
 
 
signed main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
    int n;cin>>n;
    for(int i=0;i<n;i++)cin>>valor[i+1];
    for(int i=0;i<n-1;i++){
        int a,b;cin>>a>>b;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
    for(int i=0;i<20;i++)ddp[i]=0;
 
      decomposition(1);
      //deb(tot);
    
    for(int j=1;j<=n;j++)tot+=valor[j];
 
    cout<<tot<<'\n';
}
