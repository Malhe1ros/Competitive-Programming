#include <bits/stdc++.h>
 
using namespace std;
 
#define ld long double
#define ll long long
#define int ll
#define FF first.first
#define FS first.second
#define SF second.first
#define SS second.second
#define PB push_back
#define MP make_pair
#define all(cont) cont.begin(),cont.end()
#define rall(cont) cont.rbegin(), cont.rend()
#define FOR(i, j) for(int i=0;i<j;i++)
#define RFOR(i, j) for (int i=j;i>=0;i--)
#define GO cin.tie(NULL);
#define FAST ios_base::sync_with_stdio(false);
typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;
 
 
 
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


const int MOD=1e9+7;


struct Combo {
    vector<ll> facs;
    vector<ll> invfacs;
    int N;

    Combo(int N) {
        this->N=N;
        facs.assign(N+1,0);
        invfacs.assign(N+1,0);
        facs[0] = 1;
        for (int i = 1; i <= N; i++) {
            facs[i] = (facs[i-1]*i)%MOD;
        }
        invfacs[N] = power(facs[N],MOD-2);
        for (int i = N-1; i >= 0; i--) {
            invfacs[i] = (invfacs[i+1]*(i+1))%MOD;
        }
    }
 
    ll ncr(int n, int k) {
        if (n<0||k<0||n<k) return 0LL;
        ll denInv = (invfacs[k]*invfacs[n-k])%MOD;
        ll ans = (facs[n]*denInv)%MOD;
        return ans;
    }
    
    static ll power(ll x, ll y) {
        ll ans = 1;
        x %= MOD;
        while (y > 0) {
            if (y%2==1) ans = (ans*x)%MOD;
            y /= 2;
            x = (x*x)%MOD;
        }
        return ans;
    }

    static ll invMod(ll a){
      return power(a,MOD-2);
    }
};

void minuspol(VI &cima,VI& b,int coef,int pot){
  int n=b.size();
  cima.pop_back();
  int m=cima.size();
  m--;
  for (int i=n-2;i>=0;i--){
    cima[m]-=coef*b[i];
    cima[m]%=MOD;
    cima[m]+=MOD;
    cima[m]%=MOD;
    m--;
  }
}

VI long_division(VI a,VI b){
  VI ans;
  while(a.size()>=b.size()){
    int coef=a.back()*Combo::invMod(b.back());
    coef%=MOD;
    minuspol(a,b,coef,a.size()-b.size());
    ans.PB(coef);
  }
  return ans;
}


signed main(){
  GO FAST
  VI embaixo={0,3,3,1};
  int n,qq;cin>>n>>qq;
  Combo C(3*n+10);
  VI emcima;
  FOR(i,3*n+4)emcima.PB(C.ncr(3*n+3,i));
  emcima[0]-=1;
  emcima[1]-=3;
  emcima[2]-=3;
  emcima[3]-=1;/*
  for (auto k:emcima){
    cout<<k<<" ";
  }
  cout<<endl;
  for (auto k:embaixo){
    cout<<k<<" ";
  }
  cout<<endl;*/
  //reverse(all(emcima));
  
  auto poly = long_division(emcima,embaixo);
  /*for (auto k:poly){
    cout<<k<<" ";
  }
  cout<<'\n';*/
  reverse(all(poly));
  while(qq--){
    int q;cin>>q;
    cout<<poly[q]<<'\n';
  }
}
