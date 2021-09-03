#include <bits/stdc++.h>

using namespace std;
#define int long long
const int maxn=(1<<20);
const int maxbit=20;

/*
    This is the SOS DP trick, Sum Over Subsets.
    if we need to use bitmask dynamic programming over all submasks we can do it naively in O(4^N)
    We can speed up with the submask enumeration trick to O(3^N)
    We can speed this up even further with SOS DP to O(N*2^N)
*/


signed main(){
    

    int n;cin>>n;
    vector<int>F(maxn);
    vector<int>beg(n);

    for (int i=0;i<n;i++)cin>>beg[i];

    //SOS DP over submask;
    for (int i=0;i<n;i++){
        F[beg[i]]++;
    }
    for(int i = 0;i < maxbit; ++i) for(int mask = 0; mask < (maxn); ++mask){
        if(mask & (1<<i)) F[mask] += F[mask^(1<<i)];
        
    }

    //SOS DP over supermask;
    vector<int>Fand=vector<int>(maxn);
    for(int i=0;i<n;i++){
        Fand[beg[i]]++;
    }

    for(int i = 0;i < maxbit; ++i) for(int mask = 0; mask < (maxn); ++mask){
        if(mask & (1<<i)) Fand[mask^(1<<i)] += Fand[mask];
    }

    //SOS DP over a&b!=0 = (n-(F[(maxn-1)^k]));
    
    for(auto k:beg){
        cout<<F[k]<<" "<<Fand[k]<<" "<<n-(F[(maxn-1)^k])<<"\n";
    }
}
