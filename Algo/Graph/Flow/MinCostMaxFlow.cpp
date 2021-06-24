#include <bits/stdc++.h>

//solves https://codeforces.com/contest/237/problem/E

using namespace std;
#define ll long long

const ll oo = 1e18;
const int N = 422, E = 2 * 10006;
 
struct Edge{
    int from, to; ll cap, cost;
};

struct MCMF{
    vector<int> g[N];
    int ne;


    Edge edge[E];
    int p[N]; int inqueue[N];
    ll d[N];
    ll pot[N];

    

    bool dijkstra(int source, int sink) {
        for(int i = 0; i < N; i++) d[i] = oo;
        d[source] = 0;
        priority_queue<pair<ll, int>> q;
        q.emplace(0, source);
        ll dt; int u;
        while(!q.empty()) {
            tie(dt, u) = q.top(); q.pop(); dt = -dt;
            if(dt > d[u]) continue;
            if(u == sink) return true;
            for(int e : g[u]) {
                auto v = edge[e];
                const ll cand = d[u] + v.cost + pot[u] - pot[v.to];
                if(v.cap > 0 and cand < d[v.to]) {
                    p[v.to] = e;
                    d[v.to] = cand;
                    q.emplace(-d[v.to], v.to);
                }
            }
        }
        return d[sink] < oo;
    }
    
    // <max flow, min cost>
    pair<ll, ll> mincost(int source , int sink ){
        ll ans = 0, mf = 0;
        while(dijkstra(source, sink)){
            ll f = oo;
            for(int u = sink; u != source; u = edge[ p[u] ].from)
                f = min(f, edge[ p[u] ].cap);
            mf += f;
            ans += f * (d[sink] - pot[source] + pot[sink]);
            for(int u = sink; u != source; u = edge[ p[u] ].from){
                edge[ p[u] ].cap -= f;
                edge[ p[u] ^ 1 ].cap += f;
            }
            for(int i = 0; i < N; i++) pot[i] = min(oo, pot[i] + d[i]);
        }
        return {mf, ans};
    }
    void addEdge(int u, int v, ll c, ll cost){
        assert(cost >= 0);
        edge[ne] = {u, v, c, cost};
        g[u].push_back(ne++);
        edge[ne] = {v, u, 0,-cost};
        g[v].push_back(ne++);
    }
};

MCMF fluxo;

int main(){

    string s;cin>>s;
    int t;cin>>t;
    vector<string> strin(t);
    vector<int> maximo(t);
    for(int i=0;i<t;i++){
        cin>>strin[i]>>maximo[i];
    }

    vector<int> cont(26);
    for(auto k:s){
        cont[k-'a']++;
    }

    int sourc=t+26;
    int snk=sourc+1;
    for (int i=0;i<t;i++){
        fluxo.addEdge(sourc,i,maximo[i],i+1);
    }
    for(int i=0;i<26;i++){
        fluxo.addEdge(t+i,snk,cont[i],0);
    }
    int contador=0;
    for(auto k:strin){
        vector<int> contk(26);
        for (auto k1:k){
            contk[k1-'a']++;
        }
        for(int i=0;i<26;i++){
            if (contk[i]){
                fluxo.addEdge(contador,t+i,contk[i],0);
            }
        }
        contador++;
    }
    auto ans=fluxo.mincost(sourc,snk);
    if (ans.first==s.length())cout<<ans.second<<endl;
    else cout<<-1<<endl;

    
}
