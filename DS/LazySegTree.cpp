#include <bits/stdc++.h>

using namespace std;

struct segtree{
    vector<int> seg;
    vector<int> lazy;
    int size;
    int neutro;
    int lazyneutro;
    int op(int a,int b){
        return min(a,b);
    }
    int lazyop(int a,int b){
        if (b==lazyneutro) return a;
        return b;
    }
    void propagate(int x,int lx,int rx){
        if (rx-lx==1) return;
        seg[2*x+1]=lazyop(seg[2*x+1],lazy[x]);
        seg[2*x+2]=lazyop(seg[2*x+2],lazy[x]);
        lazy[2*x+1]=lazyop(lazy[2*x+1],lazy[x]);
        lazy[2*x+2]=lazyop(lazy[2*x+2],lazy[x]);

        lazy[x]=lazyneutro;
    }
    segtree(vector<int>&v,int neu=0,int lazyneu=-1){
        int n=1;
        while(n<v.size()) n=n<<1;
        seg.assign(2*n,neu);
        lazy.assign(2*n,lazyneu);
        size=n;
        neutro=neu;
        lazyneutro=lazyneu;
        build(v,0,0,size);
    }
    void build(vector<int>& v,int x,int lx,int rx){
        if (rx-lx==1){
            if (lx<v.size()) seg[x]=v[lx];
            return;
        }
        int mid = lx + (rx-lx)/2;
        build(v,2*x+1,lx,mid);
        build(v,2*x+2,mid,rx);
        seg[x]=op(seg[2*x+1],seg[2*x+2]);
    }

    void rangeset(int l,int r,int valor,int x,int lx,int rx){
        propagate(x,lx,rx);
        if (r<=lx || l>=rx) return ;
        if (lx>=l && rx<=r){
             lazy[x]=lazyop(lazy[x],valor);
             seg[x]=lazyop(seg[x],valor);
             return;
        }
        int mid = lx+(rx-lx)/2;
        rangeset(l,r,valor,2*x+1,lx,mid);
        rangeset(l,r,valor,2*x+2,mid,rx);
        seg[x]=op(seg[2*x+1],seg[2*x+2]);
        seg[x]=lazyop(seg[x],lazy[x]);
    }
    void rangeset(int l,int r,int valor){
        rangeset(l,r,valor,0,0,size);
    }
    int query(int l,int r,int x,int lx,int rx){
        propagate(x,lx,rx);
        if (r<=lx || l>=rx) return neutro;
        if (lx>=l && rx<=r) return seg[x];
        int mid = lx+(rx-lx)/2;
        int resl=query(l,r,2*x+1,lx,mid);
        int resr=query(l,r,2*x+2,mid,rx);
        int res=op(resl,resr);
        res=lazyop(res,lazy[x]);
        return res;
    }
    
    
    
    int query(int l,int r){
        return query(l,r,0,0,size);
    }

};