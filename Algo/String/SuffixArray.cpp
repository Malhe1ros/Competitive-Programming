#include<bits/stdc++.h>

using namespace std;

struct SuffixArray{
    string s;
    int n;
    vector<int> arr;
    SuffixArray(string& _s){
        s=_s+'$';
        n=s.length();
        arr=vector<int>(n);
        build();
    }

    void counting_sort(vector<int>& p,vector<int>&c){
        vector<int>cnt(n);
        for (auto k:c) cnt[k]++;
    
        vector<int>pref(n);
        for (int i=1;i<n;i++) pref[i]=pref[i-1]+cnt[i-1];

        vector<int> ans(n);
        for (auto k:p) ans[pref[c[k]]++]=k;
        
        p=ans;   
    }

    void build(){
        vector<pair<char,int>> pares(n);
        for(int i=0;i<n;i++)pares[i]={s[i],i};
        vector<int>p(n);
        sort(pares.begin(),pares.end());
        for (int i=0;i<n;i++){
            p[i]=pares[i].second;
        }
        vector<int>eqclass(n);
        eqclass[pares[0].second]=0;
        for (int i=1;i<n;i++){
            eqclass[p[i]]=eqclass[p[i-1]];
            if (pares[i].first!=pares[i-1].first)eqclass[p[i]]++;
        }
        int k=0;
        while((1<<k) < n){

            for (int i=0;i<n;i++){
                p[i]=(p[i]-(1<<k)+n)%n;
            }
            
            counting_sort(p,eqclass);

            vector<int>neweqclass(n);
            neweqclass[p[0]]=0;
            for (int i=1;i<n;i++){
                pair<int,int> antes={eqclass[p[i-1]],eqclass[(p[i-1]+(1<<k))%n]};
                pair<int,int> depois={eqclass[p[i]],eqclass[(p[i]+(1<<k))%n]};
                neweqclass[p[i]]=neweqclass[p[i-1]];
                if (antes!=depois)neweqclass[p[i]]++;
            }
            eqclass=neweqclass;
            k++;
        }
        for (int i=0;i<n;i++)arr[i]=p[i];
    }
};


int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    string s;cin>>s;
    SuffixArray sa(s);

}
