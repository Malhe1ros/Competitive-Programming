#include<bits/stdc++.h>
 
using namespace std;
 
struct DSU{
    int* arr;
    int* size;
    stack<vector<pair<int,int>>> rb;
    int cc;
    DSU(){
 
    }
    DSU(int n){
        cc=n;
        arr = new int[n];
        for (int i=0;i<n;i++){
            arr[i]=-1;
        }
        rb.push(vector<pair<int,int>>());
    }
    int find(int a){
        while(arr[a]>=0)a=arr[a];
        return a;
    }
    void uniao(int a,int b){
        int paia=find(a);
        int paib=find(b);
        if (paia==paib)return;
        cc--;
        //paib é maior, entao liga em b
        int tam=arr[paia]+arr[paib];
        if (arr[paia]>arr[paib]){
            rb.top().push_back({paib,arr[paib]});
            rb.top().push_back({paia,arr[paia]});
            arr[paia]=paib;
            arr[paib]=tam;
        }
        else{
            rb.top().push_back({paib,arr[paib]});
            rb.top().push_back({paia,arr[paia]});
            arr[paib]=paia;
            arr[paia]=tam;
        }
    }
    void persist(){
        rb.push(vector<pair<int,int>>());
    }
    void rollback(){
        auto changes=rb.top();
        rb.pop();
        int n=changes.size();
        cc+=n/2;
        for (int i=n-1;i>=0;i--){
            arr[changes[i].first]=changes[i].second;
        }
    }
};
 
struct query{
    int beg;
    int en;
    int n1;
    int n2;
    query(int a,int b,int c,int d){
        beg=a;
        en=b;
        n1=c;
        n2=d;
    }
};
 
int n,q;
int qq;
vector<int>consulta;
vector<int> gamb;
void solve(int l,int r,int lCons,int rCons,vector<query> queries,DSU& dsu){
    while(lCons < consulta.size() && consulta[lCons] < l) lCons++;
 
  while(rCons >= 0 && consulta[rCons] >= r) rCons--;
  if(lCons == consulta.size() || rCons == -1 || lCons > rCons) return;

    if(r==l+1){
		  dsu.persist();
        for (auto k:queries){
            if (k.en!=-1 && k.beg<=l && k.en>=r ){
            dsu.uniao(k.n1,k.n2);
        }
        }
		  for (int i=lCons;i<=rCons;i++){
        if(consulta[i]==l){
          gamb.push_back(dsu.cc);
        }
      }
		  dsu.rollback();
        return;
    }
    dsu.persist();
    vector<query> q2;
	bool tq=false;
    for (auto k:queries){
 
        //significa que eu to completamente dentro, acrescento na dsu;
        if (k.beg<=l && k.en>=r ){
            dsu.uniao(k.n1,k.n2);
        }
        //significa que tem interseçao, acrescento na dsu;
        else if ( !(k.beg>=r || k.en<=l)){
            q2.push_back(k);
        }
    }
    int mid = (l+r)/2;
    solve(l,mid,lCons,rCons,q2,dsu);
    solve(mid,r,lCons,rCons,q2,dsu);
	
    dsu.rollback();
}
 
int main(){
    
 
    scanf("%d%d",&n,&q);
    DSU dsu= DSU(n);
    map<pair<int,int>,int> hash;
    vector<query> queries;
    int cont=0;
    qq=q;
    
    while(q--){
        char c;
        scanf(" %c",&c);
        if (c=='?'){
            consulta.push_back(cont);
        }
        else if (c=='+'){
            int a,b;scanf("%d%d",&a,&b);a--;b--;
			      if (a>b)swap(a,b);
            hash[{a,b}]=cont;
        }
        else{
            int a,b;scanf("%d%d",&a,&b);a--;b--;
			      if (a>b)swap(a,b);
            queries.push_back(query(hash[{a,b}],cont+1,a,b));
            hash[{a,b}]=-1;
			
        }
        cont++;
    }
    for (auto k:hash){
      if (k.second==-1)continue;
        queries.push_back(query(k.second,qq+1,k.first.first,k.first.second));
    }
    int maximo=consulta.size();
    
    solve(0,qq+1,0,maximo-1,queries,dsu);
    for (auto k:gamb){
		printf("%d\n",k);
	}
 
}
