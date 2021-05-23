#include <bits/stdc++.h>
 
using namespace std;

//solves https://oj.uz/problem/view/BOI17_railway

/*
This algorithm can sum and query the value of a path in a tree using the euler tour of the tree + a fenwick tree
*/

#define ll long long

const int maxn=1e5+10;
const int maxlog=20;

//usual fenwick tree
struct fenwick{
 
    ll* arr;
    int size;
    fenwick(int n){
        arr= new ll[n+1];
        for (int i=0;i<=n;i++) arr[i]=0;
        size=n;
    }
    fenwick(vector<int>& v){
        int n=v.size();
        arr = new ll[n+1];
        size=n;
        for (int i=0;i<n;i++){
            arr[i+1]=v[i];
        }
        build();
    }
    void build () {
        for (int i=1;i<=size;i++){
            int j= i + (i & (-i));
            if (j<=size)arr[j]+=arr[i];
        }
    }
    void update(int i,int delta){
 
        for (;i<=size;i += i&(-i)){
            arr[i]+=delta;
        }
    }
    ll query(int i){
        ll soma=0;
        for (;i;i-= i &(-i))soma+=arr[i];
        return soma;
    }
    ll query(int l,int r){
        if (l==1)return query(r);
        return query(r)-query(l-1);
    }
};
 
vector<pair<int,int>> grafo[maxn];
 
int ddepth[maxn];
int pai[maxn];
int beg[maxn]; int en[maxn]; int ver[maxn];
int tempo=0;
int dp[maxn][maxlog];
int volta[maxn];
//usual predfs + euler tour
void dfs(int u,int p,int cc=0){
    pai[u]=p;
    tempo++;
    beg[u]=tempo;
    ddepth[u]=cc;
    for (auto k:grafo[u]) if (k.first!=p){
        volta[k.first]=k.second;
        dfs(k.first,u,cc+1); 
    } 
    en[u]=tempo;
}
 
//usual binary lifting + LCA
int jmp(int a,int j){
    for (int i=0;i<maxlog;i++)if ((j>>i) & 1) a=dp[a][i];
    return a;
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
    cin.tie(NULL);cin.sync_with_stdio(false);
    int n,m,k;
    cin>>n>>m>>k;
    //usual graph reading
    for (int i=1;i<n;i++){
        int a,b;cin>>a>>b;
        grafo[a].push_back({b,i});
        grafo[b].push_back({a,i});
    }
    dfs(1,0);
 
    fenwick f(maxn);
    //usual binary lifting
    for (int i=1;i<=n;i++) dp[i][0]=pai[i];
    for (int j=1;j<maxlog;j++)for (int i=1;i<=n;i++) dp[i][j]=dp[dp[i][j-1]][j-1];
    //this is where things get interesting
    //reads all queries
    while(m--){
        int a;cin>>a;
        
        vector<int>v(a);
        for (int i=0;i<a;i++){
            cin>>v[i];
        }
        /*
            Sort by first appearence on the euler tour;
            The idea of this sorting is to enable us to find a path from LCA to v[0] then to v[1] ... then back to LCA;
            we can sum a value to the hole path from A to root using range updates on a fenwick tree
            (range update from beg[node] to en[node]+1 sums the path from node (and all of its subtree) to root)
            if we want to sum in a path from A to B we can sum the whole path from A to root then B to root, now we take -2*sum from LCA to root
        */
        sort(v.begin(),v.end(), [](int a,int b){ return beg[a]<beg[b];});
        v.push_back(v[0]);
        for (int i=0;i<a;i++){
            int l=lca(v[i],v[i+1]);
 
            f.update(beg[v[i]],1);
            f.update(beg[v[i+1]],1);
            f.update(beg[l],-2);
        }
    }
 
    vector<int> ans;
    for (int i=2;i<=n;i++){
        if (f.query(beg[i],en[i])>=2*k) ans.push_back(volta[i]);
    }
    cout<<ans.size()<<"\n";

    sort(ans.begin(),ans.end());
    for (auto k1: ans) cout<<k1<<" ";
    cout<<endl;
 
}
