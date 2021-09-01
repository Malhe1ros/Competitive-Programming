#include<bits/stdc++.h>
 
using namespace std;
 
struct SuffixArray{
    string s;
    int n;
    vector<int> arr;
    vector<int>pos;
    vector<int> LCP;
    SuffixArray(string& _s){
        s=_s+'$';
        n=s.length();
        pos=vector<int>(n);
        arr=vector<int>(n);
        LCP=vector<int>(n);
        build();
        kasai();
    }

    void kasai(){
        int k=0;
        for (int i=0;i<n-1;i++){
            int j=arr[pos[i]-1];
            while(s[i+k]==s[j+k])k++;
            LCP[pos[i]]=k;
            k=max(k-1,0);
        }
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
        for (int i=0;i<n;i++)pos[arr[i]]=i;
        
    }
    /*
    int pode(string&pat,int ind){
        for (int i=ind;i<ind+pat.size();i++){
            if (i>=n)return -1;
            if (pat[i-ind]>s[i])return 1;
            if (pat[i-ind]<s[i])return -1;
        }
        return 0;
    }
    int qntd_subst(string &pat){
        int l=0;
        int r=n;
        bool achei=0;
        while(l<r){
            int mid=(l+r)/2;
            auto teste=pode(pat,arr[mid]);
            if (teste==0)achei=1;
            if (teste>=0) l=mid+1;
            else r=mid;
        }
        if (!achei)return 0;
        int maxr=r;
        l=0;r=n;
        while(l<r){
            int mid=(l+r)/2;
            auto teste=pode(pat,arr[mid]);
            if (teste==0)achei=1;
            if (teste>0) l=mid+1;
            else r=mid;
        }
        return maxr-r;
    }
    */
 
};
 
 
int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    string s;cin>>s;
    SuffixArray sa(s);
    for (auto k:sa.arr){
        cout<<k<<" ";
    }
    cout<<'\n';
    for (int i=1;i<1+s.length();i++){
        cout<<sa.LCP[i]<<" ";
    }
    cout<<endl;
    
}
