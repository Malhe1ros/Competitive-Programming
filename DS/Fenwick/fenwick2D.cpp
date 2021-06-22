#include <bits/stdc++.h>

using namespace std;
#define ll long long

// Solves https://cses.fi/problemset/task/1739

struct fenwick2D{
    vector<vector<ll>> arr;
    int n,m;
    fenwick2D(vector<vector<int>>&v){
        n=v.size();
        m=v[0].size();
        arr = vector<vector<ll>>(n+1,vector<ll>(m+1));
        build(v);
    };

    void update(int x,int y,int val){
        for (;x<=n;x+=(x & (-x))){
            for (int i=y;i<=m;i+=(i & (-i))){
                arr[x][i]+=val;
            }
        }
    }
    ll query(int x,int y){
        ll soma=0;
        for (;x;x-= x & (-x)){
            for (int i=y;i;i-=(i & (-i)))soma+=arr[x][i];
        }
        return soma;
    }
    void build(vector<vector<int>>&v){
        for (int i=1;i<=n;i++){
            for (int j=1;j<=m;j++){
                update(i,j,v[i-1][j-1]);
            }
        }
    }
    ll query(int x2,int y2,int x1,int y1){
        return query(x1,y1)-query(x1,y2-1)-query(x2-1,y1)+query(x2-1,y2-1);
    }
};

int main(){
    int n,m;cin>>n>>m;
    vector<vector<int>>v(n,vector<int>(n));
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            char c;cin>>c;
            if (c=='*'){
                v[i][j]=1;
            }
        }
    }
    fenwick2D f= fenwick2D(v);
    while(m--){
        int tt;cin>>tt;
        if (tt==1){
            int a,b;cin>>a>>b;
            v[a-1][b-1]=1-v[a-1][b-1];
            if(v[a-1][b-1]==0)f.update(a,b,-1);
            else f.update(a,b,1);
            
        }
        else{
        int a,b,c,d;cin>>a>>b>>c>>d;
        cout<<f.query(a,b,c,d)<<endl;
        }
    }

}
