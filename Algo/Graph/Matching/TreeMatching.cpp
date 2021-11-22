#include <bits/stdc++.h>
 
using namespace std;
//solves https://codeforces.com/gym/102392/problem/F

vector<vector<int>> grafo;
vector<int> dp;//dp[i] returns the minimum number of unmatched edges on my subtree

void dfs(int u,int p){
    int tot=0;
    for(auto k:grafo[u]){
        if(k!=p){
            dfs(k,u);
            tot+=dp[k];
        }
    }
    if (tot==0)dp[u]=1;//if there is no one unmatched, i am the unmatched one
    else dp[u]=tot-1;//if there is someone unmatched, i can find an augmenting path and decrease the number of unmatched by one
}

bool TreeMatching(){
    dfs(0,-1);
    return dp[0]==0;
} 

signed main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n;cin>>n;
    grafo=vector<vector<int>>(n);
    dp=vector<int>(n);
    for(int i=0;i<n-1;i++){
        int a,b;cin>>a>>b;a--;b--;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
    if(!TreeMatching())cout<<"Alice\n";
    else cout<<"Bob\n";
}
