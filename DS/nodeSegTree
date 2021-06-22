#include "bits/stdc++.h"
using namespace std;


#define int long long
#define ll long long

struct nd{
	int x;
	nd(int a){
		x=a;
	}
	nd(){

	}
};

template<class nd>
struct segtree{
    vector<nd> seg;
    nd merge(nd a,nd b){
		return nd(a.x+b.x);
	}
    int size;
    nd neutro;
    segtree(vector<nd>&v,nd neu){
        int n=1;
        while(n<v.size()) n=n<<1;
        seg.assign(2*n,neu);

        size=n;
        neutro=neu;
        build(v,0,0,size);
    }
    void build(vector<nd>& v,int x,int lx,int rx){
        if (rx-lx==1){
            if (lx<v.size()) seg[x]=v[lx];
            return;
        }
        int mid = lx + (rx-lx)/2;
        build(v,2*x+1,lx,mid);
        build(v,2*x+2,mid,rx);
        seg[x]=merge(seg[2*x+1],seg[2*x+2]);
    }
    
    void set(int index,nd valor,int x,int lx,int rx){
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
        seg[x]=merge(seg[2*x+1],seg[2*x+2]);
    }


    void set(int index,nd valor){
        set(index,valor,0,0,size);
    }

    nd query(int l,int r,int x,int lx,int rx){
        if (r<=lx || l>=rx) return neutro;
        if (lx>=l && rx<=r) return seg[x];
        int mid = lx+(rx-lx)/2;
        return merge(query(l,r,2*x+1,lx,mid),query(l,r,2*x+2,mid,rx));
    }
    
    
    
    nd query(int l,int r){
        return query(l,r,0,0,size);
    }

};

int32_t main(){
    ll n,q;
    cin>>n>>q;
    vector<nd> v(n);
    for (ll i=0;i<n;i++){
		int a;
        cin>>a;
		v[i].x=a;
    }
	nd neu(0);
    segtree<nd> s =segtree<nd>(v,neu);
 
    ll a,b,c;
    while(q--){
        cin>>a>>b>>c;
        if (a==2){
            cout<<s.query(b,c).x<<endl;
        }
        else{
            s.set(b,c);
        }
    }
 
 
}
