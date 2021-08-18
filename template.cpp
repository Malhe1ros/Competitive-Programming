#include <bits/stdc++.h>
 
using namespace std;
 
#define ld long double
#define ll long long
//#define int ll
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
#define prec(x) cout << fixed << setprecision(x)
#define sz(x) (int)x.size()

typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;
typedef vector<VI> VVI;
typedef priority_queue<int> max_heap;
typedef priority_queue<pii> max_heapii;
typedef priority_queue<int,VI,greater<int>> min_heap;
typedef priority_queue<pii,VPII,greater<pii>> min_heapii;

const long double PI = 3.14159265359;
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

void print(vector<int>&v){
	cout<<"[";
	FOR(i,v.size()){
		cout<<v[i];
		if(i+1!=v.size())cout<<", ";
	}
	cout<<"]"<<endl;
}

void print(pii & p){
	cout<<"{"<<p.first<<", "<<p.second<<"}"<<endl;
}
 
signed main(){
	GO FAST
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		VI v(n);
		FOR(i,n)cin>>v[i];
	}
}
