#include <bits/stdc++.h>
 
using namespace std;


#define ll long long

struct fenwick{

    ll* arr;
    int size;
    fenwick(int n){
        size=n;
        arr= new ll[n+1];
        for (int i=0;i<=n;i++) arr[i]=0;
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
        for (;i<=size;i += i&(-i))arr[i]+=delta;
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


const int maxn=1e5+10;
vector<int> grafo[maxn];


int beg[maxn];
int en[maxn];
int ddepth[maxn];
int pai[maxn];
int tempo=0;
void pre(int u,int p,int cc=0){
    pai[u]=p;
    tempo++;
    beg[u]=tempo;
    ddepth[u]=cc;
    for (auto k:grafo[u]) if (k!=p) pre(k,u,cc+1);
    en[u]=tempo;
}

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    int n,k;cin>>n;
    for (int i=0;i<n-1;i++){
        int a,b;cin>>a>>b;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
    pre(1,0);
    fenwick f(maxn);
    
    while(1){
        int a,b,c;cin>>a>>b;
        if (a==1){
            f.update(beg[b],1);
            f.update(en[b]+1,-1);
        }
        else{
            cout<<f.query(beg[b])<<endl;
        }
    }

}
