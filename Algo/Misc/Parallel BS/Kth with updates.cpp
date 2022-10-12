#include <bits/stdc++.h>
 

using namespace std;

#define int long long
const int maxn = 1e5+10;


struct Query{
    int left,right,kth;
    int tempo;
    int id;
    Query(){

    }
    Query(int a,int b,int c,int d,int e){
        left=a;
        right=b;
        kth=c;
        tempo=d;
        id = e;
    }
};

struct Update{
    int ponto,newval;
    int tempo;
    int soma;
    Update(){

    }
    Update(int a,int b,int c,int d){
        ponto = a;
        newval = b;
        soma = c;
        tempo = d;
    }
};

#define ll long long

int arr[maxn];
struct fenwick{

    
    int size;
	fenwick(int n){
		size=n;	
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
        for (;i>0;i-= i &(-i))soma+=arr[i];
        return soma;
    }
    ll query(int l,int r){
        return query(r)-query(l-1);
    }
};

int n;
fenwick seg(maxn-1);
int ans[maxn];

//Binary Search on answer
void solve(int l,int r,vector<Query> q,vector<Update> up){
    if((r-l)==1 || q.empty()){//if I am at leaf, this is the answer
        for(auto k:q)ans[k.id] = l;
        return;
    }
    
    int mid = (l+r)/2;
    
    vector<Update> leftUp;
    vector<Update> rightUp;
    vector<Query> leftQuery;
    vector<Query> rightQuery;
    
    int i = 0;
    int j = 0;

    while(i<up.size() || j<q.size()){//two pointers to add all updates before time of query
        if(j==q.size() || (i<up.size() && up[i].tempo<=q[j].tempo)){//UPDATE
            //do update if before mid;
            if(up[i].newval<mid){
                seg.update(up[i].ponto,up[i].soma);
                leftUp.push_back(up[i]);
            }
            else rightUp.push_back(up[i]);
            i++;
        }
        else{
            int tot = seg.query(q[j].left,q[j].right);
            //if I have more than k, have to look in the left;
            if(tot>=q[j].kth){
                leftQuery.push_back(q[j]);
            }
            else{
                /*
                    If I have less than k, I need more on the right,
                    I am never looking for the queries on the left, 
                    so I will just decrease total I found on the left from what I need
                    In other to solve it indepently
                */
                q[j].kth-=tot;
                rightQuery.push_back(q[j]);
            }
            j++;
        }
    }
    for(auto k:leftUp) {//Remove all updates;
        seg.update(k.ponto,-k.soma);
    }
    solve(l,mid,leftQuery,leftUp);
    solve(mid,r,rightQuery,rightUp);
}

signed main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    cin>>n;
    vector<int> v(n);

    vector<Query> queries;
    vector<Update> updates;
    for(int i=0;i<n;i++){   
        cin>>v[i];
        updates.push_back(Update(i+1,v[i],1,-1));
    }

    int qid = 0;
    
    int q;cin>>q;
    for(int i=0;i<q;i++){
        int a;cin>>a;
        if(a==1){
            int b,c;
            cin>>b>>c;
            updates.push_back(Update(b,v[b-1],-1,i));
            updates.push_back(Update(b,c,1,i));
            
            v[b-1] = c;
        }
        else{
            int b,c,d;cin>>b>>c>>d;
            ans[qid] = INT_MAX;
            queries.push_back(Query(b,c,d,i,qid));
            qid++;
        }
    }

    //Binary Search on Answer
    solve(0,INT_MAX,queries,updates);

    for(int i=0;i<qid;i++)cout<<ans[i]<<" ";
    cout<<'\n';
}
