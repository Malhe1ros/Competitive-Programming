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
#define GO cin.tie(NULL);
#define FAST ios_base::sync_with_stdio(false);
#define AE cout<<"AEEEE"<<endl;
#define _L cout<<"Linha "<<__LINE__<<endl;
#define sz(x) (int)x.size()

typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;
typedef vector<VI> VVI;

//const long double PI = 3.14159265359;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll a, ll b){return uniform_int_distribution<ll>(a, b)(rng);}

#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}

void print(vector<int>v){
	cout<<"[";
	FOR(i,sz(v)){
		cout<<v[i];
		if(i+1!=sz(v))cout<<", ";
	}
	cout<<"]"<<endl;
}

void print(pii p){
	cout<<"{"<<p.first<<", "<<p.second<<"}"<<endl;
}

template<typename Container>
void print(Container beg){
    cout<<"[";
    for(auto k:beg){
        cout<<k<<" ";
    }
    cout<<"]"<<endl;
}

const long double PI = acos(-1);
typedef complex<long double> doublex;
 
void FFT(vector<doublex> &a, bool inverse) {
    int n = a.size();
    assert(n == (n & -n));
    
    vector<int> rev(n);
    for (int i = 1; i < n; i++) {
        rev[i] = (rev[i>>1]>>1) | (i&1 ? n>>1 : 0);
        if (rev[i] < i) swap(a[i], a[rev[i]]);
    }
 
    for (int m = 2; m <= n; m <<= 1) {
        long double theta = (inverse ? -1 : 1) * 2 * PI / m;
        doublex unity_root(cos(theta), sin(theta));
 
        for (int k = 0; k < n; k += m) {
            doublex omega = 1;
            for (int j = 0; j < m/2; j++) {
                doublex t = a[k + j + m/2] * omega;
                doublex u = a[k + j];
                a[k + j] = u + t;
                a[k + j + m/2] = u - t;
                omega *= unity_root;
            }
        }
    }
    for (int j = 0; inverse && j < n; j++) a[j] /= n;
}
 
//typedef long long ll;
 
vector<ll> fftsolve(vector<ll> &a, vector<ll> &b) {
    vector<doublex> ca(a.begin(), a.end()), cb(b.begin(), b.end());
    int n;
    for (n = 1; n < a.size() + b.size(); n <<= 1);
    ca.resize(n); cb.resize(n);
 
    FFT(ca, false);
    FFT(cb, false);
    for (int i = 0; i < n; i++) ca[i] *= cb[i];
    FFT(ca, true);
 
    vector<ll> ret(n);
    for(int i = 0; i < n; i++) ret[i] = round(ca[i].real());
    return ret;
}

VI solve(VI& a,VI& b,bool pqp){
	int n=sz(a);
	int l=0;
	int r=n-1;
	VI ans;

	while(l<=r){
		int teste=-1;
		if(a[l]*b[l]>a[r]*b[r]){
			teste=max(teste,a[l]*b[l]);
			if(teste>=0)l++;
		}
		else{
			teste=max(teste,a[r]*b[r]);
			if(teste>=0)r--;
		}
		if(teste<0)break;
		ans.PB(teste);
		
	}

	VI A;
	VI B;
	for(int i=l;i<=r;i++){
		A.PB(a[i]);
		B.PB(b[i]);
	}

	if(!A.empty() && A[0]>0){
		sort(all(A));
		sort(rall(B));
	}
	else{
		sort(rall(A));
		sort(all(B));
	}

	auto ansk=fftsolve(A,B);

	for(int i=1;i<sz(ans);i++)ans[i]+=ans[i-1];
	int gamb=0;
	if(!ans.empty())gamb=ans.back();

	for(auto k:ansk){
		ans.PB(gamb+k);
		if(sz(ans)>=n)break;
	}

	return ans;
}

signed main(){
	GO FAST
	int n;
	cin>>n;
	VI a(n);
	VI b(n);
	FOR(i,n)cin>>a[i];
	FOR(i,n)cin>>b[i];
	sort(all(a));
	sort(all(b));
	VI maxi=solve(a,b,1);
	//exit(0);
	for(auto& k:a)k=-k;
	reverse(all(a));
	//sort(all(a));
	//sort(all(b));
	VI mini=solve(a,b,0);
	FOR(i,n){
		cout<<-mini[i]<<" "<<maxi[i]<<'\n';
	}
}
