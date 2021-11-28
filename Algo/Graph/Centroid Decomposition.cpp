#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn=2e5+10;
vector<int> grafo[maxn];//graph
bool rm[maxn];//is removed?
int sub[maxn];//subtree size;

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

vector<int> centroidtree[maxn];
int root=-1;
int decomposition(int u=0){//doesn't matter which beggining node, calculates the centroid decomposition of the tree;
    int centroid=get_centroid(u,dfs(u));
    if (root==-1)root=centroid;
    rm[centroid]=1;
    for(auto k:grafo[centroid]){
        if (!rm[k]){
            auto l1=decomposition(k);
            centroidtree[centroid].push_back(l1);
            centroidtree[l1].push_back(centroid);
        }
    }
    return centroid;
}



signed main(){
    int n;cin>>n;
    for(int i=0;i<n-1;i++){
        int a,b;cin>>a>>b;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
    decomposition(1);
}
