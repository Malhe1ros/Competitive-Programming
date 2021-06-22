#include <bits/stdc++.h>

//Solves https://cses.fi/problemset/task/1648/
using namespace std;
#define ll long long

struct fenwick{

    ll* arr;
    int size;
	fenwick(int n){
		size=n;
		arr=new ll[n+1];
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

int main(){
    int n,q;scanf("%d%d",&n,&q);
    vector<int>v(n);
    for (auto &k:v)scanf("%d",&k);
    fenwick f= fenwick(v);
    
    while(q--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        if (a==1){
            f.update(b,-v[b-1]);
            f.update(b,c);
            v[b-1]=c;
        }
        else{
            //cout<<"b "<<b<<endl;
            //cout<<f.query(b)<<endl;

            printf("%lld\n",f.query(b,c));
        }
    }
}
