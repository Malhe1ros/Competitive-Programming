#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
#define int long long

//solves https://codeforces.com/problemset/problem/622/F

//Done in O(N) (logN with inverses but optimizable);
 
const int MOD=1e9+7;

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

//assumes x={0,1,2,3,...,n}
//it is easy to change range to {x,x+1,...,x+n};
int interpolate(vector<int>& y,int u){
  int n=y.size();
  vector<int> suf(n+1,1);
  vector<int> fat(n,1);
  for(int i=n-1;i>=0;i--) suf[i]=(suf[i+1]*(u-i))%MOD;
  for(int i=1;i<n;i++)fat[i]=(i*fat[i-1])%MOD;
  int pref=1;
  int ans=0;
  for(int i=0;i<n;i++){
    int num=(pref*suf[i+1])%MOD;
    int den=(fat[i]*fat[n-1-i])%MOD;

    
    int toad=(y[i]*num)%MOD;
    toad*=invMod(den);
    toad%=MOD;
    if((n-1-i)%2)toad*=-1;
    ans+=toad;
    ans%=MOD;
    pref*=(u-i);
    pref%=MOD;
  }
  return ans;
  
}
 
 

signed main(){
  int n,k;cin>>n>>k;
  vector<int>y(k+2);
  for(int i=1;i<=(k+1);i++){
    y[i]=(y[i-1]+power(i,k))%MOD;
  }
  
  cout<<(interpolate(y,n)+MOD)%MOD<<'\n';
}
