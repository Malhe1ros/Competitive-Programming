#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#include <ext/random>
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
 
void print(pii p){
	cout<<"{"<<p.first<<", "<<p.second<<"}"<<endl;
}
 
 
class SuffixArray {
public:
	template<class T>
	std::vector<int> buildSuffix(const T &array) {
		int n = array.size();
		std::vector<int> sa(n);
		for(int i = 0; i < n; i++) {
			sa[i] = i;
		}
		std::sort(sa.begin(), sa.end(), [&](int a, int b) { return array[a] < array[b]; });
		int cur = 0;
		std::vector<int> inv(n);
		std::vector<int> nxt(n);
		inv[sa[0]] = 0;
		for(int i = 1; i < n; i++) {
			inv[sa[i]] = (array[sa[i - 1]] != array[sa[i]] ? ++cur : cur);
		}
		cur++;
		for(int k = 0; cur < n; k++) {
			cur = 0;
			auxSort(sa, inv, 1 << k);
			for(int l = 0, r = 0; l < n; l = r, cur++) {
				while(r < n && getPair(inv, sa[l], 1 << k) == getPair(inv, sa[r], 1 << k)) {
					nxt[sa[r++]] = cur;
				}
			}
			nxt.swap(inv);
		}
		return sa;
	}
 
	template<class T>
	std::vector<int> buildLCP(const std::vector<int> &sa, const T &array) {
		int n = sa.size();
		std::vector<int> inv(n);
		for(int i = 0; i < n; i++) {
			inv[sa[i]] = i;
		}
		std::vector<int> lcp(n, 0);
		for(int i = 0, k = 0; i < n; i++) {
			if(inv[i] + 1 == n) {
				k = 0;
				continue;
			}
			int j = sa[inv[i] + 1];
			while(i + k < n && j + k < n && array[i + k] == array[j + k]) {
				k++;
			}
			lcp[inv[i]] = k;
			if(k > 0) {
				k--;
			}
		}
		return lcp;
	}
private:
	void auxSort(std::vector<int> &sa, const std::vector<int> &inv, int offset) {
		// O(nlogn) step, O(nlog^2n) total
		std::sort(sa.begin(), sa.end(), [&](int a, int b) { return getPair(inv, a, offset) < getPair(inv, b, offset); });
		// O(n) step, O(nlogn) total -- TO DO --
	}
	std::pair<int, int> getPair(const std::vector<int> &inv, int pos, int offset) {
		return std::pair<int, int>(inv[pos], pos + offset < (int) inv.size() ? inv[pos + offset] : -1);
	}
};
 
 
const int maxn = 5e5+10;
int ps[maxn];
int getSum(int l,int r){//[l,r]
    int antes = 0;
    if(l>0)antes = ps[l-1];
    return ps[r] - antes;
}
 
typedef tree<
pii,
null_type,
less<pii>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;
 
map<int,int> ide;
ordered_set gamb;
void adiciona(int u){
    if(ide.find(u)==ide.end())ide[u] = 0;
    gamb.insert(MP(u,ide[u]));
    ide[u]++;
}
 
int query(int l,int r){
    return gamb.order_of_key(MP(r,INT_MAX)) - gamb.order_of_key(MP(l,-1));
}
 
signed main(){
    GO FAST
    SuffixArray SA;
    int n,L,R;cin>>n>>L>>R;
    VI v(n);
    FOR(i,n)cin>>v[i];
    ps[0] = v[0];
    for(int i=1;i<n;i++){
        ps[i] = ps[i-1]+v[i];
    }
    auto sa = SA.buildSuffix(v);
    auto lcp  = SA.buildLCP(sa,v);
    int apartir = 0;
    int tot = 0;
    VPII queries;
    
    FOR(i,n){
        int antes = 0;
        if(sa[i]!=0)antes = ps[sa[i]-1];
        queries.push_back(MP(sa[i]+apartir,antes));
        apartir = lcp[i];
    }
    sort(rall(queries));
    int onde = n-1;
    for(auto k:queries){
       // print(k);
        while(k.first<=onde){
            adiciona(ps[onde]);
            onde--;
        }
        tot+=query(L+k.second,R+k.second);
       
    }
 
    cout<<tot<<'\n';
  
}
