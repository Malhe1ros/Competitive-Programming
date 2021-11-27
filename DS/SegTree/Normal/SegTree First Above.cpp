#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
 
 
struct segtree{
    vector<long long> seg;
    
    long long size;
    long long neutro;
    long long f(long long a,long long b){
        return max(a,b);
    }
    segtree(vector<long long>&v,long long neu=0){
        long long n=1;
        while(n<v.size()) n=n<<1;
        seg.assign(2*n,neu);
 
        size=n;
        neutro=neu;
        build(v,0,0,size);
    }
    void build(vector<long long>& v,long long x,long long lx,long long rx){
        //cout<<x<<" "<<lx<<" "<<rx<<endl;
        if (rx-lx==1){
            if (lx<v.size()) seg[x]=v[lx];
            return;
        }
        long long mid = lx + (rx-lx)/2;
        build(v,2*x+1,lx,mid);
        build(v,2*x+2,mid,rx);
        seg[x]=f(seg[2*x+1],seg[2*x+2]);
    }
    
    void set(long long index,long long valor,long long x,long long lx,long long rx){
        if(rx-lx==1){
            seg[x]=valor;
            return;
        }
        long long mid=lx+(rx-lx)/2;
        if (index<mid){
            set(index,valor,2*x+1,lx,mid);
        }
        else{
            set(index,valor,2*x+2,mid,rx);
        }
        seg[x]=f(seg[2*x+1],seg[2*x+2]);
    }
 
 
    void set(long long index,long long valor){
        set(index,valor,0,0,size);
    }
 
    int first_above(ll n,int j,ll x,ll lx,ll rx){
        if (rx-lx==1 && seg[x]>=n){
            if (lx>=j) return lx;
            return -1;
        }
        if (seg[x]<n) return -1;
        int mid = lx + (rx-lx)/2;
        int opt1=-1;
        if (seg[x]>=n && j<rx)opt1=first_above(n,j,2*x+1,lx,mid);
        if (opt1==-1){
            opt1=first_above(n,j,2*x+2,mid,rx);
        }
        return opt1;
    }
 
    int first_above(ll n,int j){
        return first_above(n,j,0,0,size);
    }
 
};
 
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    vector<ll> v(n);
    for (auto &k:v) scanf("%lld",&k);
    segtree st=segtree(v,INT_MIN);
 
    while(m--){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        if (a==1){
            
            st.set(b,c);
        }
        else{
            auto t=st.first_above(b,c);
            cout<<t<<endl;
 
        }
    
    }
}
