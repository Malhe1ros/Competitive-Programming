#include <bits/stdc++.h>
using namespace std;

/*
    this is black magic;
    how to use it, calculate the 10(+) first terms of the recurrence relation
    v={first 10(+) terms}
    and plug on guess_nth_term(v,k) and it will return recurrence[k];
*/

#define sz(v) (int)(v.size())

typedef long long ll;

const int mod = 1e9+7;

ll mul(ll x, ll y, ll modc){ return (__int128) x * y % modc; }
ll ipow(ll x, ll y, ll p = mod){
 ll ret = 1, piv = x % p;
 while(y){
  if(y&1) ret = mul(ret, piv, p);
  piv = mul(piv, piv, p);
  y >>= 1;
 }
 return ret;
}

vector<int> berlekamp_massey(vector<int> x){
 vector<int> ls, cur;
 int lf, ld;
 for(int i=0;i<sz(x);i++){
  ll t = 0;
  for(int j=0;j<sz(cur);j++){
   t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
  }
  if((t - x[i]) % mod == 0) continue;
  if(cur.empty()){
   cur.resize(i+1);
   lf = i;
   ld = (t - x[i]) % mod;
   continue;
  }
  ll k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
  vector<int> c(i-lf-1);
  c.push_back(k);
  for(auto &j : ls) c.push_back(-j * k % mod);
  if(sz(c) < sz(cur)) c.resize(sz(cur));
  for(int j=0;j<sz(cur);j++){
   c[j] = (c[j] + cur[j]) % mod;
  }
  if(i-lf+sz(ls)>=sz(cur)){
   tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
  }
  cur = c;
 }
 for(auto &i : cur) i = (i % mod + mod) % mod;
 return cur;
}

int get_nth(vector<int> rec, vector<int> dp, ll n){
 int m = sz(rec);
 vector<int> s(m), t(m);
 s[0] = 1;
 if(m != 1) t[1] = 1;
 else t[0] = rec[0];
 auto mul = [&rec](vector<int> v, vector<int> w){
  vector<int> ans(2 * sz(v));
  for(int j=0;j<sz(v);j++){
   for(int k=0;k<sz(v);k++){
    ans[j+k] += 1ll * v[j] * w[k] % mod;
    if(ans[j+k] >= mod) ans[j+k] -= mod;
   }
  }
  for(int j=2*sz(v)-1; j>=sz(v); j--){
   for(int k=1; k<=sz(v); k++){
    ans[j-k] += 1ll * ans[j] * rec[k-1] % mod;
    if(ans[j-k] >= mod) ans[j-k] -= mod;
   }
  }
  ans.resize(sz(v));
  return ans;
 };
 while(n){
  if(n & 1) s = mul(s, t);
  t = mul(t, t);
  n >>= 1;
 }
 ll ret = 0;
 for(int i=0;i<m;i++) ret += 1ll * s[i] * dp[i] % mod;
 return ret % mod;
}

vector<int> coef; //imprimir vetor coef na main
int guess_nth_term(vector<int> x, ll n){
 if(n < sz(x)) return x[n];
 coef = berlekamp_massey(x);
 if(coef.empty()) return 0;
 return get_nth(coef, x, n);
}

int main() {
	
    //used to solve https://codeforces.com/gym/102966/problem/F
	int n;
	vector<int> iniciais={16, 600, 4680, 19904, 61000, 152136, 329280, 642560, 1158624, 1963000, 3162456, 4887360};
	while(cin>>n){
		n--;
   		cout << guess_nth_term(iniciais, n) << endl;
	}
}
