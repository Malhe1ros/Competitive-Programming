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


ll pow(ll base, ll p, ll MOD)
{
	if(p == 0) return 1;
	if(p % 2 == 0) { ll d = pow(base, p / 2, MOD); return (d * d) % MOD; }
	return (pow(base, p - 1, MOD) * base) % MOD;
}
 
ll inv(ll x, ll MOD) { return pow(x, MOD - 2, MOD); }
 
vector<ll> gauss(vector<vector<ll> > &a, ll MOD)
{
	int n = a.size(), m = a[0].size() - 1;
    //cout << n << " " << m << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= m; j++){
		    //cout << a[i][j] << " ";
			a[i][j] = (a[i][j] % MOD + MOD) % MOD;
	    }
	    //cout << endl;
    }
	vector<int> where(m, -1);
	for(int col = 0, row = 0; col < m && row < n; col++)
	{
		int sel = row;
		for(int i = row; i < n; i++)
			if(a[i][col] > a[sel][col])
				sel = i;
 
			if(a[sel][col] == 0) { where[col] = -1; continue; 
	}
        for(int i = col; i <= m; i++)
			swap(a[sel][i], a[row][i]);
		where[col] = row;
 
		ll c_inv = inv(a[row][col], MOD);
		for(int i = 0; i < n; i++)
			if(i != row)
			{
				if(a[i][col] == 0) continue;
			    	ll c = (a[i][col] * c_inv) % MOD;
			    	for(int j = 0; j <= m; j++)
				    a[i][j] = (a[i][j] - c * a[row][j] % MOD + MOD) % MOD;
			}
 
		row++;
    }
    vector<ll> ans(m, 0);
    ll result = 1;
    // for counting rank, take the count of where[i]==-1
    for(int i = 0; i < m; i++)
        if(where[i] != -1) ans[i] = (a[where[i]][m] * inv(a[where[i]][i], MOD)) % MOD;
		else result = (result * MOD) % MOD;
	// This is validity check probably.May not be needed
    for(int i = 0; i < n; i++)
	{
		ll sum = a[i][m] % MOD;
		for(int j = 0; j < m; j++)
			sum = (sum + MOD - (ans[j] * a[i][j]) % MOD) % MOD;
	}
 
	return ans;
}

map<pii,int> id;
VPII recomv;
VVI oscara;
void le(){
	int tot;cin>>tot;
	int t;cin>>t;
	VI v(t);
	FOR(i,t)cin>>v[i];
	VI kkk;
	for(int i=1;i<t;i++){
		pii p={min(v[i-1],v[i]),max(v[i-1],v[i])};
		if(id.find(p)==id.end()){
			id[p]=sz(id);
			recomv.PB(p);
		}
		kkk.PB(id[p]);
	}
	kkk.PB(tot);
	oscara.PB(kkk);
}


const int INF=1e18;
struct dijkstra{
	int n;
	vector<vector<pair<int,int>>> grafo;
	dijkstra(int _n){
		n=_n;
		grafo=vector<vector<pair<int,int>>>(n);
	}
	
	void addEdge(int a,int b,int c){
		grafo[a].push_back({b,c});
	}

	//calculates value of shortest path from a to b;
	int min_path(int a,int b){
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap;
		vector<int>dp(n,INF);
		dp[a]=0;
		heap.push({0,a});
		while(!heap.empty()){
			auto olhando=heap.top();
			heap.pop();
			if (olhando.second==b)break;
			if (olhando.second!=a && dp[olhando.second]<olhando.first) continue;
			for (auto k:grafo[olhando.second]){
				if (dp[k.first]>dp[olhando.second]+k.second){
					dp[k.first]=dp[olhando.second]+k.second;
					heap.push({dp[k.first],k.first});
				}
			}
		}
		return dp[b];
	}

	//calculates all values of shortest path from a to all nodes;
	vector<int> min_path(int a){
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap;
		vector<int>dp(n,INF);
		dp[a]=0;
		heap.push({0,a});
		while(!heap.empty()){
			auto olhando=heap.top();
			heap.pop();
			if (olhando.second!=a && dp[olhando.second]<olhando.first) continue;
			for (auto k:grafo[olhando.second]){
				if (dp[k.first]>dp[olhando.second]+k.second){
					dp[k.first]=dp[olhando.second]+k.second;
					heap.push({dp[k.first],k.first});
				}
			}
		}
		return dp;
	}

	//returns the shortest path from a to b;
	vector<int> path(int a,int b){
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap;
		vector<int>dp(n,INF);
		vector<int> ultimo(n,-1);
		dp[a]=0;
		heap.push({0,a});
		while(!heap.empty()){
			auto olhando=heap.top();
			heap.pop();
			if (olhando.second==b)break;
			if (olhando.second!=a && dp[olhando.second]<olhando.first) continue;
			for (auto k:grafo[olhando.second]){
				if (dp[k.first]>dp[olhando.second]+k.second){
					dp[k.first]=dp[olhando.second]+k.second;
					ultimo[k.first]=olhando.second;
					heap.push({dp[k.first],k.first});
				}
			}
		}
		int beg=b;
		vector<int> ans;
		while(beg!=-1){
			ans.push_back(beg);
			beg=ultimo[beg];
		}
		reverse(ans.begin(),ans.end());
		return ans;
	}
};

signed main(){
	int n,a,b,t;cin>>n>>a>>b>>t;
	while(t--){
		le();
	}
	vector<VI> gaussiar;
	for(auto k:oscara){
		VI v(sz(id));
		FOR(i,sz(k)-1){
			v[k[i]]++;
		}
		v.PB(k.back());
		gaussiar.PB(v);
	}
	auto ans=gauss(gaussiar,13);
	dijkstra dij(n+2);
	FOR(i,sz(recomv)){
		dij.addEdge(recomv[i].first,recomv[i].second,ans[i]);
		dij.addEdge(recomv[i].second,recomv[i].first,ans[i]);
	}
	cout<<dij.min_path(a,b)<<'\n';
}
