#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define pii pair<ll,ll>

class edge{
  public:
  int to,cap,rev;
  edge(int t,int c,int r): to{t},cap{c},rev{r}
  {}
};
/* Computes maximum flow in O(E*V^2)
How to use:
create an object dinic(number of nodes, source node,sink node);
add directed edges to the graph with addEdge(begin,end,capacity) function;
compute the flow with fluxo();
*/


class dinic{
  public:
    vector<vector<edge>> grafo;
    vector<int> levelgraph;
    vector<bool> deadend;
    int n,s,t;
    dinic(int n,int s,int t){
      grafo = vector<vector<edge>>(n,vector<edge>());
      this->n=n;
      this->s=s;
      this->t=t;
    }
    void addEdge(int a,int b,int c){
      grafo[a].push_back({b,c,(int)grafo[b].size()});
      grafo[b].push_back({a,0,(int)grafo[a].size()-1});
    }
    void bfs(){
      levelgraph=vector<int>(n,-1);
      levelgraph[s]=0;
      queue<int> q;
      q.push(s);
      while(!q.empty()){
          int olhando =q.front();
          q.pop();
          for (auto k:grafo[olhando]){
            if (k.cap>0 && levelgraph[k.to]==-1){
              levelgraph[k.to]=levelgraph[olhando]+1;
              q.push(k.to);
            }
          }
      }
    }
    int dfs(int index,int flow){
      if (index==t) return flow;
      for (auto&k:grafo[index]){
        if (k.cap>0 && levelgraph[k.to]==levelgraph[index]+1 && !deadend[k.to]){
          int maybe_flow = dfs(k.to,min(flow,k.cap));
          k.cap-=maybe_flow;
          grafo[k.to][k.rev].cap+=maybe_flow;
          if (maybe_flow!=0) return maybe_flow;
        }
      }
      deadend[index]=true;
      return 0;
    }
    int fluxo(){
      int f=0;
      while(true){
        bfs();
        deadend=vector<bool>(n,false);
        if (levelgraph[t]==-1) break;
        int f_maybe=-1;
        while(f_maybe!=0){
          f_maybe=dfs(s,INT_MAX);
          f+=f_maybe;
        }
      }
      return f;
    }
    
};
