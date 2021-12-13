#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
#define int long long
//Done in O(N^2)

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

struct LagrangeInterpolation{
  vector<int> x;
  vector<int> y;
  vector<int> weights;
  int n;
  LagrangeInterpolation(vector<int> _x,vector<int> _y){//sz(x)==sz(y);
    x=_x;
    y=_y;
    n=x.size();
    weights.resize(n);
    for(int i=0;i<n;i++){
      int tot=1;
      for(int j=0;j<n;j++){
        if(i==j)continue;
        tot*=(x[i]-x[j]);
        tot%=MOD;
      }
      weights[i]=invMod(tot);
    }
  }

  int calcL(int u){
    int tot=1;
    for(int i=0;i<n;i++){
      tot*=(u-x[i]);
      tot%=MOD;
    }
    return tot;
  }

  int query(int u){
    for(int i=0;i<n;i++){
      if(u==x[i])return y[i];
    }
    int soma=0;
    for(int i=0;i<n;i++){
      int delta=weights[i]*y[i];
      delta%=MOD;
      int dq=u-x[i];
      if (u<x[i]){
        dq=MOD-dq;
      }
      delta*=invMod(dq);
      soma+=delta;
      soma%=MOD;  
    }
    return (calcL(u)*soma)%MOD;
  }
};



//FLOAT VERSION

/* 

#define ld long double
struct LagrangeInterpolation{
  vector<ld> x;
  vector<ld> y;
  vector<ld> weights;
  int n;
  LagrangeInterpolation(vector<ld> _x,vector<ld> _y){//sz(x)==sz(y);
    x=_x;
    y=_y;
    n=x.size();
    weights.resize(n);
    for(int i=0;i<n;i++){
      int tot=1;
      for(int j=0;j<n;j++){
        if(i==j)continue;
        tot*=(x[i]-x[j]);
      }
      weights[i]=(ld)(1.0/tot);
    }
  }

  ld calcL(ld u){
    ld tot=1;
    for(int i=0;i<n;i++){
      tot*=(u-x[i]);
    }
    return tot;
  }

  ld query(ld u){
    for(int i=0;i<n;i++){
      if (x[i]==u)return y[i];
    }
    ld soma=0;

    for(int i=0;i<n;i++){
      ld delta=weights[i]*y[i];
      delta/=(u-x[i]);
      soma+=delta;
    }

    return (calcL(u)*soma);
  }
};
*/
signed main(){
  cout<<fixed<<setprecision(6);
  int n,k;cin>>n>>k;
  vector<int>x(k+2);
  vector<int>y(k+2);
  for(int i=0;i<(k+2);i++){
    x[i]=i+1;
    y[i]=power(i+1,k);
    if(i)y[i]+=y[i-1];
  }
  
  LagrangeInterpolation ip(x,y);
  cout<<(ip.query(n)+MOD)%MOD<<'\n';
}
