#include<bits/stdc++.h>

/*
Solves https://codeforces.com/contest/600/problem/E
ARPA'S TRICK OR SACK IS A TECHNIQUE TO QUERY STUFF ABOUT ALL SUBTREES OF A TREE IN N*logN TIME
THE IDEIA IS TO USE SMALL TO LARGE MERGING, EVERY TIME WE WANT SOMETHING WE KEEP THE HEAVY SUBTREE ALREADY CALCULATED AND RECALCULATE THE ANSWERS OF THE LIGHT SUBTREES
THIS IDEA IS VERY POWERFUL AND SOLVES A LOT OF PROBLEMS, IT USES THE EULER TOUR OF THE TREE TO ENABLE US TO QUICKLY AND EASILY "DFS" A WHOLE SUBTREE 
IT IS A TRICK THAT SOMETIMES CAN SUBSTITUTE HEAVY LIGHT DECOMPOSITION, CENTROID DECOMPOSITION AND LOWEST COMMOM ANCESTOR QUERIES; (OBSVIOUSLY EASIER TO CODE)
TBH IT IS A BIT OF BLACK MAGIC BUT IF YOU WANNA LEARN MORE:https://codeforces.com/blog/entry/44351
*/

using namespace std;
#define ll long long
 
const int maxn =1e5+10;
int tempo=0;
vector<int>grafo[maxn];


int cnt[maxn];//data structure to store the answers

//EULER TOUR STUFF
int beg[maxn];//the first time i passed at node n;
int en[maxn];//the last time i passed at node n;
int ver[maxn];//where i was at time t;
int cor[maxn]; //the information of node n;
int sz[maxn];// the size of the subtree of node n;

//DFS to calculate euler tour stuff
void calc_h(int u,int p){
  ver[tempo]=u;
  beg[u]=tempo++;
  sz[u]=1;
  for (auto k:grafo[u]){
    if (k!=p){
      calc_h(k,u);
      sz[u]+=sz[k];
    }
  }
  en[u]=tempo;
}

long long ans[maxn];// vector with offline answers;
int qntd[maxn];// auxiliar vector for the problem;
void dfs(int u,int p,bool keep=0){
  int bigc=-1;
  int maxs=-1;
  //i find the big child;
  for (auto k:grafo[u]){
    if (k!=p){
      if (sz[k]>maxs){
        maxs=sz[k];
        bigc=k;
      }
    }
  }
  //DFS all the other children and *NOT STORE* the answers;
  for (auto k:grafo[u]){
    if (k!=p && k!=bigc) dfs(k,u);
  }
 
  if (maxs!=-1){
    dfs(bigc,u,1);//DFS the big child and *STORE* the answers
    long long maior=qntd[bigc];
    ans[u]=ans[bigc];
    cnt[cor[u]]++;
    if (cnt[cor[u]]>maior){
      maior=cnt[cor[u]];
      ans[u]=cor[u];
    }
    else if (cnt[cor[u]]==maior)ans[u]+=cor[u];
    //recalculate the answer for the smaller children;
    for (auto k:grafo[u]){
      if (k!=p && k!=bigc){
        for (int i=beg[k];i<en[k];i++){
          int k1=ver[i];
          cnt[cor[k1]]++;
          if (cnt[cor[k1]]>maior){
            maior=cnt[cor[k1]];
            ans[u]=cor[k1];
          }
          else if (cnt[cor[k1]]==maior){
            ans[u]+=cor[k1];
          }
        }
      }
      
    }
    qntd[u]=maior;
  }
  else{
    cnt[cor[u]]++;
    qntd[u]=1;
    ans[u]=cor[u];
  }
  //REMOVE THE INFORMATION OF THE NODE IF NECESSARY;
  if (!keep){
    for (int i=beg[u];i<en[u];i++){
      cnt[cor[ver[i]]]--;
    }
  }
}
 
 
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  int n;cin>>n;
  for (int i=1;i<=n;i++)cin>>cor[i];
  for (int i=0;i<n-1;i++){
    int a,b;cin>>a>>b;
    grafo[a].push_back(b);
    grafo[b].push_back(a);
  }
 
  calc_h(1,0);
  
  dfs(1,0,1);
  for (int i=1;i<=n;i++)cout<<ans[i]<<" ";
  cout<<endl;
}
