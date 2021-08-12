#include <bits/stdc++.h>
 
using namespace std;
 
#define ld long double
#define ll long long
//#define int ll
#define FF first.first
#define FS first.second
#define SF second.first
#define SS second.second
#define PB push_back
#define MP make_pair
#define all(cont) cont.begin(),cont.end()
#define rall(cont) cont.rbegin(), cont.rend()
#define FOR(i, j) for(int i=0;i<j;i++)
#define RFOR(i, j) for (int i=j;i>=0;i--)
#define GO cin.tie(NULL);
#define FAST ios_base::sync_with_stdio(false);
typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;
 
 
 
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}

const int INF=1e9;
struct hopcroft_karp{
    int part;
    int size;
    vector<vector<int>> graph;
    int* par;
    int* dist; 

    hopcroft_karp(int n,int m){

        part=n;
        size=n+m;
        graph=vector<vector<int>>(size+1);
        par=new int[size+1];
        dist = new int[size+1];
    }

    void add_edge(int u,int v){
        graph[u].push_back(part+v);
    }

    bool dfs(int u){
        if (u!=0){
        for (auto k:graph[u]){
            if (dist[par[k]]==dist[u]+1){
                if (dfs(par[k])){
                    par[k]=u;
                    par[u]=k;
                    return true;
                }
            }
            
        }
        dist[u]=INF;
        return false;
        }
        return true;
    }

    bool bfs(){
        queue<int> fila;
        for (int i=1;i<=part;i++){
            if (par[i]==0){
                dist[i]=0;
                fila.push(i);
            }
            else dist[i]=INF;
        }
        dist[0]=INF;
        while(!fila.empty()){
            auto u=fila.front();
            fila.pop();
            if (dist[u]<dist[0]){
                for (auto k:graph[u]){
                    if (dist[par[k]]==INF){
                        dist[par[k]]=dist[u]+1;
                        fila.push(par[k]);
                    }
                }
            }
        }
        return dist[0]!=INF;

    }
    int match(){
        fill(par,par+size+1,0);
        fill(dist,dist+size+1,0);
        int ans=0;
        while(bfs()){
            for (int i=1;i<=part;i++){
                if (par[i]==0 && dfs(i))ans++;
            }
        }
        return ans;
    }    


};



int main(){
    GO FAST
    int n,m,q;
    cin>>n>>m>>q;

    hopcroft_karp hkk(n,m);
    while(q--){
        int a,b;cin>>a>>b;
        hkk.add_edge(a,b);
    }

    cout<<hkk.match()<<'\n';
    for(int i=1;i<=n;i++){
        if (hkk.par[i]!=0){
            cout<<i<<" "<<hkk.par[i]-n<<'\n';
        }
    }
}
