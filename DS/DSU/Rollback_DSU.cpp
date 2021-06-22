#include<bits/stdc++.h>
using namespace std;


struct DSU{
    int* arr;
    int* size;
    stack<vector<pair<int,int>>> rb;
    int cc;
    DSU(int n){
        cc=n-1;
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

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    int n,q;cin>>n>>q;
    DSU dsu=DSU(n+1);
    while(q--){
        string s;
        cin>>s;
        if (s[0]=='p'){
            dsu.persist();
        }
        else if (s[0]=='r'){
            dsu.rollback();
            cout<<dsu.cc<<endl;
        }
        else{
            int a,b;cin>>a>>b;
            dsu.uniao(a,b);
            cout<<dsu.cc<<endl;
        }
    }
}
