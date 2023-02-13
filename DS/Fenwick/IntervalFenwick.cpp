#include <bits/stdc++.h>

using namespace std;

#define int long long

#define MAXN 2010
struct intervalFenwick{
    set<pair<int,int>> bit[MAXN];
    int par[MAXN];

    intervalFenwick(){
        memset(par, -1, sizeof par);
    }
    
    /*
        Retrieves and removes the id of all (a,b) st. a<=x && b<=y;
        To change the sign just do x = MAXN-x or similar;
    */
    vector<int> query( int x, int y ){

        vector<int> ans;
        x++;
        while(x > 0){ 
            auto ub = bit[x].upper_bound({y, INT_MAX});
            auto it = bit[x].begin();
            while(it != ub){
                if(par[it->second] == -1){
                    ans.push_back(it->second);
                    par[it->second] = 0; // (1) if you comment this doesn't remove
                }
                it = bit[x].erase(it);// (2) if you comment this doesn't remove
                //it++; //(3) uncomment this
            }
            x -= x & (-x);
        }
        return ans;
    }
    /*
        Adiciona o ponto (x,y) com 0 <= x < MAXN
        0 <= id < MAXN
    */
    void update( int x, int y, int id ){
        x++;
        while(x < MAXN){
            bit[x].insert({y, id});
            x += x & (-x);
        } 
    }
};

const int MOD= 1e9+7;

const int far  = (int)1e10;
pair<int,int> calcInv(int x,int y){
    return make_pair(2*y - (far-x),2*y + (far-x));
}



signed main(){

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n,q;cin>>n>>q;
    vector<int> caras;
    vector<pair<int,int>> quem(n);
    for(int i = 0;i<n;i++){
        int x,y;
        cin>>x>>y;
        auto ans = calcInv(x,y);
        quem[i] = ans;
        caras.push_back(ans.first);
        caras.push_back(ans.second);
    }
    sort(caras.begin(),caras.end());
    caras.erase(unique(caras.begin(),caras.end()),caras.end());

    auto getVal = [&](int x){
        return lower_bound(caras.begin(),caras.end(),x) - caras.begin();
    };

    for(int i = 0;i<n;i++) quem[i] = make_pair(getVal(quem[i].first),getVal(quem[i].second));
    
    intervalFenwick f;
    for(int i = 0;i<n;i++){
        f.update(quem[i].first,quem[i].second,i);        
    }

    auto getLb = [&](int x){
        auto it = lower_bound(caras.begin(),caras.end(),x);
        if(it==caras.end())return -1ll;
        return *it;
    };

    auto getUb = [&](int x){
        auto it = lower_bound(caras.begin(),caras.end(),x);
        if(it==caras.end()){
            it--;
            return *it;
        }
        if(*it==x)return x;
        it--;
        return *it;
    };

    int p = 0;
    const int pm = 5782344;
    auto calc = [&](int a,int b){
        //cout<<a<<" "<<b<<endl;
        auto ans = f.query(a,b);
        int t = 0;
        sort(ans.begin(),ans.end());
        int mult = 1;
        
        for(int i = 0;i<ans.size();i++){
            //cout<<ans[i]+1<<": ";
            t+=(mult*(ans[i]+1))%MOD;
            t%=MOD;
            mult*=pm;
            mult%=MOD;
        }
        //cout<<endl;
        return t;
    };

    while(q--){
        int a,b;cin>>a>>b;
        
        a = -1 - ((p+a)%MOD);
        b = (p+b)%MOD;
       
        auto ans = calcInv(a,b);

        a = ans.first;
        b = ans.second;

        a = getLb(a);
        b = getUb(b);

        

        if(a!=-1){
            if(a<=b)p = calc(getVal(a),getVal(b));
        }
        //p=calc();

        cout<<p<<'\n';
        //return 0;
    }
}
