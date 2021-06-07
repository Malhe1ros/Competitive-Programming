#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ld long double
#define ll long long
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

typedef pair<int,int> pii;

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

struct fenwick{

    ll* arr;
    int size;
    fenwick(int n){
        arr= new ll[n+1];
        size=n;
        for (int i=0;i<=n;i++){
            arr[i]=0;
        }
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

const int maxn=1e5+10;//MAXN
const int magic=320;//SQRT(MAXN)
vector<vector<pair<pii,int>>> queries(magic);// all blocks of queries;
int ans[maxn];// array with offline answers;
int caras[maxn];// array from problem

//que is a vector with the queries, {{right,left}, index}
// ind is the block i am answering queries;
void MO(vector<pair<pii,int>>& que,int ind){
    fenwick f(maxn);
    sort(all(que));//sorting the queries by right pointer;
    int i=0;
    ind*=magic;
    for(;i<que.size();i++){//solves all queries with size<= sqrt(n);
        auto primeiro=que[i].FS;
        auto segundo=que[i].FF;
        if (segundo<ind+magic){
            int invcount=0;
            for (int j=segundo;j>=primeiro;j--){
                invcount+=f.query(caras[j]-1);
                f.update(caras[j],1);
            }
            for (int j=primeiro;j<=segundo;j++){
                f.update(caras[j],-1);
            }
            ans[que[i].second]=invcount;
        }
        else break;
    }

    int j=ind+magic;
    int invcount=0;
    for (;i<que.size();i++){//solves queries that begin in this block and end after
        int primeiro=que[i].FS;
        int segundo=que[i].FF;
        for (;j<=segundo;j++){//add information until the next right pointer
            invcount+=f.query(maxn)-f.query(caras[j]);
            f.update(caras[j],1);
        }
        auto cop=invcount;
        for (int k=ind+magic-1;k>=primeiro;k--){//add the [left,BLOCK] information
            invcount+=f.query(caras[k]-1);
            f.update(caras[k],1);
        }
        ans[que[i].second]=invcount;
        for (int k=ind+magic-1;k>=primeiro;k--){//removes the information
            f.update(caras[k],-1);
        }
        invcount=cop;
    }
}

int32_t main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n,q;cin>>n>>q;
    vector<int>v(n);
    FOR(i,n){
        cin>>v[i];
        caras[i]=v[i];
    }
    auto v1=v;
    //this is just a coordinate compression
    sort(all(v1));
    unordered_map<int,int> mapa;
    int c=1;
    mapa[v1[0]]=c;
    
    for (int i=1;i<n;i++){
        if (v1[i]!=v1[i-1])c++;
        mapa[v1[i]]=c;
    }
    FOR (i,n)caras[i]=mapa[caras[i]];
    FOR(i,q){
        int l,r;
        cin>>l>>r;
        queries[l/magic].PB({{r-1,l},i});//push queries by block;
    }
    FOR(i,magic){//call MO for all blocks;
        MO(queries[i],i);
    }
    FOR(i,q)cout<<ans[i]<<" ";
    cout<<'\n';
}
