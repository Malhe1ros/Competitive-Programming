#include <bits/stdc++.h>
 
using namespace std;
//solves https://codeforces.com/contest/1614/problem/E

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


const int maxn=2e9+1e6;
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
        segtree[index]=Node(-1,-1,maxn-1,lazyneutro);//begin with all zeros;
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

    void createchilds(int u,int lx,int rx){
        int mid = lx+(rx-lx)/2;
        if (segtree[u].l==-1){
            segtree[u].l=index;
            segtree[index]=Node(-1,-1,mid-1,lazyneutro);
            index++;
        }
        if (segtree[u].r==-1){
            segtree[u].r=index;
            segtree[index]=Node(-1,-1,rx-1,lazyneutro);
            index++;
        }
    }

    void pushlazy(int u,int l,int r){
        if ((r-l)!=1){//if i am not at a leaf
            createchilds(u,l,r);
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

    int findleft(int x,int lx,int rx,int u){
        pushlazy(x,lx,rx);
        if (segtree[x].val<u)return -INT_MAX;
        if (rx-lx==1)return lx;
        int mid = lx+(rx-lx)/2;
        auto a1=findleft(segtree[x].l,lx,mid,u);
        if (a1==-INT_MAX) {
            return findleft(segtree[x].r,mid,rx,u);
        }
        return a1;
    }
    int findleft(int u){//finds the leftmost element greater than or equal to u;
        return findleft(0,0,maxn,u);
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

ImplicitSegTree<323456> seg(INT_MIN,0);
int query(int u){
    return seg.query(u,u+1);
}
void update(int u){
    int L=seg.findleft(u);
    int R=seg.findleft(u+1);
    //deb(L,R);
    if(0<L)seg.update(0,L,1);
    if(R<maxn)seg.update(R,maxn,-1);
}


const int MOD=1e9+1;
signed main(){
    /*
    while(1){
        int a,b;cin>>a>>b;
        if (a==1){
            cout<<seg.findleft(b)<<'\n';
        }
        else{
            int c,d;
            cin>>c>>d;
            seg.update(b,c,d);
        }
    }*/
	int n;cin>>n;
    int lastans=0;
    
    for(int i=0;i<n;i++){
        int Q;cin>>Q;
        
        update(Q);
        int q;cin>>q;
        while(q--){
            int a;cin>>a;
            a+=lastans;
            a%=MOD;
            lastans=query(a);
            cout<<lastans<<'\n';
        }
    }
}
