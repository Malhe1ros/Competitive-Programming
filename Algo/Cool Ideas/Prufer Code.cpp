/*
  Solves: https://atcoder.jp/contests/abc303/tasks/abc303_h

  The problem is: given a sequence of k integers A = {a1,a2,a3,...,ak}

  We want to find how many trees have all their node degree in A

  Example, if A = {1,3}, we only have 4 trees, choose a node to have degree 3 and we're done.

  The idea of this problem is to use prufer's code:
  
  Prufer's ideia is: given a tree, returns a sequence of N-2 integers

  Prufer's algorithms works in the following way:
    Take the leaf with the lowest id
    Push back the parent on the sequence
    Keep going

  If we have the prufer code = {3,4} we know:
  1 and 2 have degree 1
  3 and 4 have degree 2

  Now we transform the problem to be: create a sequence of N-2 integers, such that each integer appear a1-1 or a2-1 or a3-1... an-1 times

  This can be acomplished by saying: we can only use the numbers a1-1,a2-1...an-1, we have to use them N times and we have to get a sum of N-2, how many ways can we achieve this?

  The polinomial will be f(x) = x^(a1-1)/(a1-1)! + x^(a2-1)/(a2-1)! + x^(a3-1)/(a3-1)! ... 

  We have to find the [n-2] coefficient of f(x)^N, we have to divide by b! because of the terms in the multinomial theorem
  
  This is well known to be solved by fast exponentiation and FFT, in the end we have no multiply by (n-2)!
*/

#include <bits/stdc++.h>
#include <ext/random>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

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
#define GO cin.tie(NULL);
#define FAST ios_base::sync_with_stdio(false);
#define AE cout<<"AEEEE"<<endl;
#define _L cout<<"Linha "<<__LINE__<<endl;
#define sz(x) (int)x.size()
 
typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;
typedef vector<VI> VVI;
 
const long double PI = 3.14159265359;
__gnu_cxx::sfmt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll a, ll b){return uniform_int_distribution<ll>(a, b)(rng);}
 
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}
 
template<typename Container>
void print(Container beg){
    cout<<"[";
    for(auto k:beg){
        cout<<k<<" ";
    }
    cout<<"]"<<endl;
}
 
void print(vector<int>v){
	cout<<"[";
	FOR(i,sz(v)){
		cout<<v[i];
		if(i+1!=sz(v))cout<<", ";
	}
	cout<<"]"<<endl;
}




typedef complex<double> C;


void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		for(int i=k;i<2*k;i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vector<int> rev(n);
	for(int i=0;i<n;i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for(int i=0;i<n;i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) for(int j=0;j<k;j++) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}

template<int M> 
vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
	if (a.empty() || b.empty()) return {};
	vector<ll> res(sz(a) + sz(b) - 1);
	int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int32_t(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n);
	for(int i=0;i<sz(a);i++) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
	for(int i=0;i<sz(b);i++) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	for(int i=0;i<n;i++){
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	for(int i=0;i<sz(res);i++){
		ll av = (ll)(real(outl[i])+.5), cv = (ll)(imag(outs[i])+.5);
		ll bv = (ll)(imag(outl[i])+.5) + (ll)(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}

const ll MOD=998244353;

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
int n;
VI solve(VI x, ll y) {
    VI ans = {1};
    while (y > 0) {
        if (y%2==1){
          ans = convMod<MOD>(ans,x);
          while(!ans.empty() && (ans.back()==0 || ans.size()>n-1))ans.pop_back();
        }
        y /= 2;
        x = convMod<MOD>(x,x);
        while(!x.empty() && (x.back()==0 || x.size()>n-1))x.pop_back();
    }
    return ans;
}

signed main(){
  GO FAST
  int k;cin>>n>>k;
  VI pol(n);
  Combo C(2*n);
  FOR(i,k){
    int x;cin>>x;
    pol[x-1]++;
  }
  while(pol.back()==0)pol.pop_back();
  FOR(i,sz(pol)){
    pol[i]*=C.invfacs[i];
  }
  VI ans = solve(pol,n);
  if(ans.size()<=n-2){
    cout<<0<<'\n';
    return 0;
  }
  cout<<(ans[n-2]*C.facs[n-2])%MOD<<'\n';
}
