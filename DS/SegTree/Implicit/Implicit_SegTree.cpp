#include <bits/stdc++.h>
 
using namespace std;

#define int long long

struct Node{
    int l,r,val,lazy;
    Node(){

    }
    Node(int a,int b,int c,int d){
        l=a;
        r=b;
        val=c;
        lazy=d;
    }
};


const int maxn=1e9+10;
template<int MAXV>
struct ImplicitSegTree{
    Node segtree[64*MAXV];//to store my implicit segtree
    int index=0;//which indice am i looking?
    const int beg=0;
    const int en=maxn;//[beg,en[ is the range of my segtree;
    int lazyneutro;//this value means there is no lazy to be pushed;
    int neutro;//this value is the neutral element of op operation

    ImplicitSegTree(int neu,int lneutro){
        lazyneutro=lneutro;
        neutro=neu;
        segtree[index]=Node(-1,-1,0,lazyneutro);//begin with all zeros;
        index++;
    }

    int lazyop(int a,int b){//will be used to lazy update;
        return a+b;
    }

    int op(int a,int b){//will be used to range query;
        return max(a,b);
    }

    void applylazyatnode(int u,int l,int r){//will be used to apply the lazy update at the node;
        segtree[u].val=lazyop(segtree[u].val,segtree[u].lazy);
        segtree[u].lazy=lazyneutro;
    }

    void createchilds(int u){
        if (segtree[u].l==-1){
            segtree[u].l=index;
            segtree[index]=Node(-1,-1,0,lazyneutro);
            index++;
        }
        if (segtree[u].r==-1){
            segtree[u].r=index;
            segtree[index]=Node(-1,-1,0,lazyneutro);
            index++;
        }
    }

    void pushlazy(int u,int l,int r){
        if ((r-l)!=1){//if i am not at a leaf
            createchilds(u);
            segtree[segtree[u].l].lazy=lazyop(segtree[u].lazy,segtree[segtree[u].l].lazy);
            segtree[segtree[u].r].lazy=lazyop(segtree[u].lazy,segtree[segtree[u].r].lazy);
        }
        
        if(segtree[u].lazy!=lazyneutro) applylazyatnode(u,l,r);
        
    }

    int query(int x,int lx,int rx,int l,int r){
        pushlazy(x,lx,rx);
        if (l<=lx && rx<=r){
            return segtree[x].val;
        }
        if (lx>=r || rx<=l)return neutro;

        int mid=lx+(rx-lx)/2;
        return op(query(segtree[x].l,lx,mid,l,r),query(segtree[x].r,mid,rx,l,r));

    }

    //[l,r[
    int query(int l,int r){
        return query(0,beg,en,l,r);
    }

    void update(int x,int lx,int rx,int l,int r,int val){
        pushlazy(x,lx,rx);
        if (lx>=r || rx<=l)return;
        if (lx>=l && rx<=r){
            segtree[x].lazy=lazyop(val,segtree[x].lazy);
            pushlazy(x,lx,rx);
            return;
        }
        int mid = lx+(rx-lx)/2;
        update(segtree[x].l,lx,mid,l,r,val);
        update(segtree[x].r,mid,rx,l,r,val);
        segtree[x].val=op(segtree[segtree[x].l].val,segtree[segtree[x].r].val);
    }
    void update(int l,int r,int val){
        update(0,beg,en,l,r,val);
    }
    
};

signed main(){


}
