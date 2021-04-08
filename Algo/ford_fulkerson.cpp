#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define pii pair<int,int>

class edge{
  public:
  int to,cap,rev;
  edge(int t,int c,int r): to{t},cap{c},rev{r}
  {}
};
/*
O(E*F) where F is the maximum flow
How to use:
create an object ford_fulkerson(number of nodes, source node,sink node);
add directed edges to the graph with addEdge function;
compute the flow with calc();
*/
class ford_fulkerson{
  public:
  vector<vector<edge>> grafo;
  vector<bool> vistos;
  int s,t;

  ford_fulkerson(int n,int s,int t){
    grafo=vector<vector<edge>>(n,vector<edge>());
    this->s=s;
    this->t=t;
  }
  void addEdge(int from,int to,int cap){
    grafo[from].push_back({to,cap,(int)grafo[to].size()});
    grafo[to].push_back({from,0,(int)grafo[from].size()-1});
  }
  int fluxo(int nodeatual,int fluxomaximo){
    vistos[nodeatual]=true;
    if (nodeatual==t) return fluxomaximo;
    for (auto& k:grafo[nodeatual]){
      if (!vistos[k.to] && k.cap>0){
        int maybe_flow=fluxo(k.to,min(fluxomaximo,k.cap));
        k.cap-=maybe_flow;
        grafo[k.to][k.rev].cap+=maybe_flow;
        if (maybe_flow) return maybe_flow;
      }
    }
    return 0;
  }
  int calc(){
    int fluxototal=0;
    int last=-1;
    while(last!=0){
      vistos=vector<bool>(grafo.size(),false);
      last=fluxo(s,INT_MAX);
      fluxototal+=last;
    }
    return fluxototal;
  }
};
