#include <bits/stdc++.h>
    
using namespace std;
 
#define ll long long
const int maxn=16;
int valor[maxn][maxn];

//solves https://atcoder.jp/contests/dp/tasks/dp_u
/*
    This is the submask enumeration trick.
    It is a trick used in bitmask dynamic programming to iterate over all submasks of a mask
    If we would do it naively it would cost O(4^N);
    With the SOS trick it costs O(3^N);
    It uses bit magic i would not bother to explain (because i don't know how it works lol);
    But the only import part is that for loop on the solve function, that loop iterates over all subsets;
*/

vector<ll> dp((1<<maxn),-1);
vector<ll> dp1((1<<maxn),-1);
ll calc(int bitmask){
    if (dp1[bitmask]!=-1)return dp1[bitmask];    
    int l1b=(bitmask) & (-bitmask);
    int menor= bitmask-l1b;
    dp1[bitmask]= calc(menor);
    int l1bind;
    for (int i=0;i<maxn;i++){
        if ((l1b>>i) & 1) l1bind=i;
    }

    for (int i=0;i<maxn;i++){
        if ((menor>>i) & 1) dp1[bitmask]+=valor[l1bind][i];
    }
    return dp1[bitmask];

}

ll solve(int bitmask){//THIS ITERATES OVER ALL SUBMASKS OF MASK BITMASK
    if (dp[bitmask]!=-1) return dp[bitmask];
    dp[bitmask]=calc(bitmask);
    for (int s=bitmask; s; s=(s-1)&bitmask){// THIS IS THE IMPORTANT BIT MAGIC PART
        dp[bitmask]=max(dp[bitmask],calc(s)+solve(bitmask-(bitmask & s)));
    }
    return dp[bitmask];

}

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    int n;cin>>n;
    
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) cin>>valor[i][j];
    dp1[0]=0;
    cout<<solve((1<<(n))-1)<<endl;
}
