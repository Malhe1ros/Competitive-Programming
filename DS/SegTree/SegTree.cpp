#include <bits/stdc++.h>

using namespace std;
#define ll int

struct segtree{
    vector<int> seg;
    
    int size;
    int neutro;
    int f(int a,int b){
        return min(a,b);
    }
    segtree(vector<int>&v,int neu=0){
        int n=1;
        while(n<v.size()) n=n<<1;
        seg.assign(2*n,neu);

        size=n;
        neutro=neu;
        build(v,0,0,size);
    }
    void build(vector<int>& v,int x,int lx,int rx){
        //cout<<x<<" "<<lx<<" "<<rx<<endl;
        if (rx-lx==1){
            if (lx<v.size()) seg[x]=v[lx];
            return;
        }
        int mid = lx + (rx-lx)/2;
        build(v,2*x+1,lx,mid);
        build(v,2*x+2,mid,rx);
        seg[x]=f(seg[2*x+1],seg[2*x+2]);
    }
    
    void set(int index,int valor,int x,int lx,int rx){
        if(rx-lx==1){
            seg[x]=valor;
            return;
        }
        int mid=lx+(rx-lx)/2;
        if (index<mid){
            set(index,valor,2*x+1,lx,mid);
        }
        else{
            set(index,valor,2*x+2,mid,rx);
        }
        seg[x]=f(seg[2*x+1],seg[2*x+2]);
    }


    void set(int index,int valor){
        set(index,valor,0,0,size);
    }
    //l=0,r=3,x=0,lx=0,rx=8
    int query(int l,int r,int x,int lx,int rx){
        if (r<=lx || l>=rx) return neutro;
        if (lx>=l && rx<=r) return seg[x];
        int mid = lx+(rx-lx)/2;
        return f(query(l,r,2*x+1,lx,mid),query(l,r,2*x+2,mid,rx));
    }
    
    
    
    int query(int l,int r){
        return query(l,r,0,0,size);
    }

};


int main(){
    int n,m;
    cin>>n>>m;
    
    vector<int> v(n);
    for (int i=0;i<n;i++){
        cin>>v[i];
    }

    segtree st = segtree(v,INT_MAX);




    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        if (a==1){
            st.set(b,c);
        }
        else{
            //cout<<st1.sum(b,c)<<endl;
            cout<<st.query(b,c)<<endl;
        }

    }
}
