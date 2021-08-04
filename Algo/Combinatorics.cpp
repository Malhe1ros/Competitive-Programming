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
    
    ll power(ll x, ll y) {
        ll ans = 1;
        x %= MOD;
        while (y > 0) {
            if (y%2==1) ans = (ans*x)%MOD;
            y /= 2;
            x = (x*x)%MOD;
        }
        return ans;
    }

    ll invMod(ll a){
      return power(a,MOD-2);
    }
};
 
signed main(){
  GO FAST
  
  int n;cin>>n;
  Combo c(3*n);
  vector<vector<int>>dp(3*n+1,vector<int>(3));
  dp[0][0]=n;
  dp[0][1]=n;
  dp[0][2]=n;
  const int i3=c.invMod(3);
  for (int i=1;i<=3*n;i++){
    //deb(i);
    int k0=dp[i-1][0];
    int k1=dp[i-1][1];
    int alfa=c.ncr(3*n,i+1);
    //deb(i);
    dp[i][0]=((alfa-2*k0-k1)*i3)%MOD;
    dp[i][1]=k0+dp[i][0];
    dp[i][1]%=MOD;
    dp[i][2]=k1+dp[i][1];
    dp[i][2]%=MOD;
    //deb(i);
  }
  int q;cin>>q;
  while(q--){
    int a;cin>>a;
    //deb(a);
    cout<<(dp[a][0]+MOD+c.ncr(3*n,a))%MOD<<'\n';
  }  
}
