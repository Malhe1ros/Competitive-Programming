#include <bits/stdc++.h>

    
using namespace std;

#define ld long double
#define ll long long
//#define int long long
#define FF first.first
#define FS first.second
#define SF second.first
#define SS second.second
#define PB push_back
#define MK make_pair
#define all(cont) cont.begin(),cont.end()
#define rall(cont) cont.rbegin(), cont.rend()
#define FOR(i, j) for(int i=0;i<j;i++)
#define RFOR(i, j) for (int i=j;i>=0;i--)

typedef pair<int,int> PII;

// Your function
//DEBBUGGING STUFF, JUST USE deb(a,b,c) and it will print the variables;
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}

int f(int a,int b){
    return a^b;
}

struct segtree{
    vector<int> seg;
    
    int size;
    int neutro;
    
    segtree(){

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

const int maxn=2e5+10;
struct HLD{
    vector<vector<int>>tree;
    vector<int>valor;
    int pai[maxn];
    int ddepth[maxn];
    int sz[maxn];
    int heavy[maxn];
    int heavysz[maxn];
    int posinseg[maxn];
    int nxt[maxn];
    segtree paths;
    vector<int>conv;
    HLD(vector<vector<int>>&t,vector<int>&v){
        tree=t;
        
        dfs(0,-1);
        conv.PB(0);
        hld_dfs(0,-1,0);
        for(auto k:conv){
            valor.PB(v[k]);
        }
        for(int i=0;i<conv.size();i++){
            posinseg[conv[i]]=i;
        }
        paths=segtree(valor);
    }
    void dfs(int u,int p,int dd=0){
        pai[u]=p;
        ddepth[u]=dd;
        sz[u]=1;
        for (auto k:tree[u]){
            if (k!=p){
                dfs(k,u,dd+1);
                sz[u]+=sz[k];
                if (heavysz[u]<sz[k]){
                    heavysz[u]=sz[k];
                    heavy[u]=k;
                }
            }
        }
    }
    void hld_dfs(int u,int p,int papa){
        conv.PB(u);
        nxt[u]=papa;
        if(heavy[u]!=0){
            hld_dfs(heavy[u],u,papa);
        }
        for(auto k:tree[u]){
            if (k!=heavy[u] && k!=pai[u]){
                hld_dfs(k,u,k);
            }
        }
    }

    void update(int v,int u){
        paths.set(posinseg[v],u);
    }

    int query(int a,int b){
        int paia=nxt[a];
        int paib=nxt[b];
        if(paia==paib){
            int x=posinseg[a];
            int y=posinseg[b];
            if(x>y)swap(x,y);
            return paths.query(x,y+1);
        }
        if(ddepth[nxt[a]]<ddepth[nxt[b]])swap(a,b);
        return f(paths.query(min(posinseg[nxt[a]],posinseg[a]),max(posinseg[nxt[a]],posinseg[a])+1),query(pai[nxt[a]],b));
        
    }
};


int32_t main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n,q;cin>>n>>q;
    vector<int>valor(n);
    for(auto &k:valor)cin>>k;
    vector<vector<int>>tree(n);
    FOR(i,n-1){
        int a,b;cin>>a>>b;a--;b--;
        tree[a].PB(b);
        tree[b].PB(a);
    }
    HLD hld(tree,valor);
  
    while(q--){
        int a,b,c;
        cin>>a>>b>>c;
        if(a==1){
            b--;
            hld.update(b,c);
        }
        else{
            b--;c--;
            cout<<hld.query(b,c)<<"\n";
        }
    }

}
