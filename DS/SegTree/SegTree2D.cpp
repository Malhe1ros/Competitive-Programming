#include <bits/stdc++.h>
 
using namespace std;
//solves https://atcoder.jp/contests/abc228/tasks/abc228_f

int f(int a,int b){
    return max(a,b);
}

struct segtree{
    vector<int> seg;
    
    int size;
    int neutro;
    segtree(int n,int neu=0){
        size=1;
        while(size<n) size=size<<1;
        seg.assign(2*size,neu);
        neutro=neu;
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

struct segtree2D{
    vector<segtree> seg;
    int sizex;
    int sizey;
    int neutro;

    segtree2D(vector<vector<int>>&v,int neu=0){
        int n=1;
        while(n<v.size()) n=n<<1;
        

        sizex=n;
        n=1;
        while(n<v[0].size())n=n<<1;
        sizey=n;
        seg.assign(2*sizex,segtree(sizey,neu));
        
        neutro=neu;
        build(v,0,0,sizex);
    }
    
    void build(vector<vector<int>>&v,int x,int lx,int rx){
        if (rx-lx==1){
            if (lx<v.size()){
                
                seg[x]=segtree(v[lx],neutro);
            }
            return;
        }
        int mid=(lx+rx)/2;
        build(v,2*x+1,lx,mid);
        build(v,2*x+2,mid,rx);
        for(int i=0;i<seg[x].seg.size();i++){
            seg[x].seg[i]=f(seg[2*x+1].seg[i],seg[2*x+2].seg[i]);
        }
    }

    int query(int d,int u,int l,int r,int x,int lx,int rx){
        if (u<=lx || d>=rx) {
            
            return neutro;

        }
        if (lx>=d && rx<=u) {
            return seg[x].query(l,r);
        }
        int mid = lx+(rx-lx)/2;
        return f(query(d,u,l,r,2*x+1,lx,mid),query(d,u,l,r,2*x+2,mid,rx));
    }

    int query(int d,int u,int l,int r){
        u++;r++;
        return query(d,u,l,r,0,0,sizex);
    }

    void update_y(int u,int ind,int x,int lx,int rx){
        seg[u].seg[x]=f(seg[2*u+1].seg[x],seg[2*u+2].seg[x]);
        if (rx-lx==1){
            return;
        }
        int mid=(lx+rx)/2;
        if(mid>ind)update_y(u,ind,2*x+1,lx,mid);
        else update_y(u,ind,2*x+2,mid,rx);


    }

    void update_x(int cx,int cy,int val,int x,int lx,int rx){
        if (rx-lx==1){
            seg[x].set(cy,val);
            return;
        }
        int mid = (lx+rx)/2;
        if (mid>cx)update_x(cx,cy,val,2*x+1,lx,mid);
        else update_x(cx,cy,val,2*x+2,mid,rx);
        update_y(x,cy,0,0,sizey);
    }

    void update(int x,int y,int val){
        update_x(x,y,val,0,0,sizex);
    }
};



signed main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    int h,w;cin>>h>>w;
    int h1,w1,h2,w2;cin>>h1>>w1>>h2>>w2;
    int piorx=h2-1;
    int piory=w2-1;
    h2=min(h2,h1);
    w2=min(w2,w1);
    VVI v(h,VI(w));
    FOR(i,h)FOR(j,w){
        cin>>v[i][j];
    }
    FOR(i,h){
        FOR(j,w){
            if (i!=0)v[i][j]+=v[i-1][j];
            if (j!=0)v[i][j]+=v[i][j-1];
            if (((i!=0) && (j!=0)))v[i][j]-=v[i-1][j-1];
            //v[i][j]=v[i-1][j]+v[i][j-1];
        }
    }/*
    for(auto k:v){
        print(k);
    }
    cout<<endl;*/
    VVI cara1(h,VI(w));
    VVI cara2(h,VI(w));
    FOR(i,h){
        FOR(j,w){
            cara1[i][j]=v[i][j];
            if (i>=h1)cara1[i][j]-=v[i-h1][j];
            if (j>=w1)cara1[i][j]-=v[i][j-w1];
            if ((i>=h1) && (j>=w1)) cara1[i][j]+=v[i-h1][j-w1];
            cara2[i][j]=v[i][j];
            if (i>=h2)cara2[i][j]-=v[i-h2][j];
            if (j>=w2)cara2[i][j]-=v[i][j-w2];
            if ((i>=h2) && (j>=w2)) cara2[i][j]+=v[i-h2][j-w2];
        }
    }/*
    for(auto k:cara1){
        print(k);
    }
    cout<<endl;
    for(auto k:cara2){
        print(k);
    }
    cout<<endl;*/
    segtree2D seg(cara2,INT_MIN);
    int melhor=0;
    FOR(i,h){
        FOR(j,w){
            if (((i+1)>=h1) && ((j+1)>=w1)){
                //if (piorx>(i-h1+h2))continue;
                //if (piory>(j-w1+w2))continue;
                //deb(i,j);
                //deb(i,j,cara1[i][j],seg.query(i-h1+h2,i,j-w1+w2,j));
                
                melhor=max(melhor,cara1[i][j]-seg.query(i-h1+h2,i,j-w1+w2,j));
            }
        }
    }
    cout<<melhor<<'\n';
}
