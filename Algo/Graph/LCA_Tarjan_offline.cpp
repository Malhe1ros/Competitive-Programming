#include <bits/stdc++.h>
 
using namespace std;
//solves https://cses.fi/problemset/task/1688

struct DSU{
    int* arr;
    DSU(int size){
        arr = new int[size];
        
        for (int i=0;i<size;i++){
            arr[i]=-1;
        }
    }
    int find(int a){
        int ac=a;
        while(arr[a]>=0){
            a=arr[a];
        }
        while(arr[ac]>=0){
            int cop=arr[ac];
            arr[ac]=a;
            ac=cop;
        }

        return a;
    }
    void unir(int a,int b){
        int paia=find(a);
        int paib=find(b);
        if (paia==paib) return;
        int tam=arr[paia]+arr[paib];
        if (arr[paia]>arr[paib]){
            arr[paia]=paib;
            arr[paib]=tam;
        }
        else{
            arr[paib]=paia;
            arr[paia]=tam;
        }
    }
};

const int maxn=2e5+10;
vector<int> grafo[maxn];
vector<pair<int,int>> queries[maxn];
int ancestor[maxn];
vector<bool> visited(maxn,false);
DSU dsu = DSU(maxn);
int cont=1;
int ans[maxn];
void LCA(int i){
   
    visited[i]=true;
    ancestor[i]=i;
    for (auto k:grafo[i]){
        if (!visited[k]){
            LCA(k);
            dsu.unir(i,k);
            ancestor[dsu.find(i)]=i;
        }
    }
    for (auto k:queries[i]){
        if (visited[k.first]){
            ans[k.second]=ancestor[dsu.find(k.first)];
        }
    }
}

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    int n,q;cin>>n>>q;
    for (int i=2;i<=n;i++){
        int a;cin>>a;
        grafo[i].push_back(a);
        grafo[a].push_back(i);
    }
    /*for (int i=1;i<=n;i++){
        for (auto k:grafo[i]) cout<<k<<" ";
        cout<<endl;
    }*/
    for (int i=0;i<q;i++){
        int a,b;
        cin>>a>>b;
        queries[a].push_back({b,i});
        queries[b].push_back({a,i});
    }
    LCA(1);
    for (int i=0;i<q;i++){
        cout<<ans[i]<<'\n';
    }

}
