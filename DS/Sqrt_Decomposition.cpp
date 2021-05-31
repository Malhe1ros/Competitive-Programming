#include <bits/stdc++.h>

#define int long long

using namespace std;

// solves https://cses.fi/problemset/result/2248421/
/*
    Create = O(N);
    Update = O(1);
    Query = O(sqrt N);
*/

//Data structure to maintain data in sqrt chunks
struct sqrt_decomp{
    const static int maxn = 2e5+10;// maxn
    const static int magic= 450;//approximately sqrt(maxn) 
    int sqr[magic];
    int arr[maxn];
    
    //Constructor to decompose vector into the data structure
    sqrt_decomp(vector<int>&v){
        int n=v.size();
        for (int i=0;i<n;i++)arr[i]=v[i];
        for (int i=0;i<n;i++){
            sqr[i/magic]+=arr[i];
        }
    }
    //updates point a to value v
    void update(int a,int v){
        sqr[a/magic]-=arr[a];
        arr[a]=v;
        sqr[a/magic]+=arr[a];
    }

    //returns the value of [0,t]
    int query(int t){
        int total=0;
        for (int i=0;i<t/magic;i++){
            total+=sqr[i];
        }
        for (int i=(t/magic)*magic;i<=t;i++)total+=arr[i];
        return total;
    }

    //returns the value of [a,b];
    int query(int a,int b){
        if (a==0) return query(b);
        return query(b)-query(a-1);
    }

};

int32_t main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    int n,q;cin>>n>>q;
    vector<int>v(n);
    for (auto &k:v)cin>>k;
    sqrt_decomp decompoton = sqrt_decomp(v);
    while(q--){
        int a,b,c;
        cin>>a>>b>>c;
        if (a==1){
            b--;
            decompoton.update(b,c);
        }
        else{
            b--;c--;
            cout<<decompoton.query(b,c)<<'\n';
        }
    }
}
