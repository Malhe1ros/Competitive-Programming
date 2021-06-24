#include <bits/stdc++.h>

//solves https://codeforces.com/contest/237/problem/E
#include <bits/extc++.h>
using namespace std;
#define ll long long

const ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;
typedef pair<int,int> pii;
struct MCMF {
	int N;
	vector<vector<int>> ed, red;
	vector<VL> cap, flow, cost;
	vector<int> seen;
	VL dist, pi;
	vector<pii> par;

	MCMF(int N) :
		N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap),
		seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		this->cap[from][to] = cap;
		this->cost[from][to] = cost;
		ed[from].push_back(to);
		red[to].push_back(from);
	}

	void path(int s) {
		fill(seen.begin(),seen.end(), 0);
		fill(dist.begin(),dist.end(), INF);
		dist[s] = 0; ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({0, s});

		auto relax = [&](int i, ll cap, ll cost, int dir) {
			ll val = di - pi[i] + cost;
			if (cap && val < dist[i]) {
				dist[i] = val;
				par[i] = {s, dir};
				if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
				else q.modify(its[i], {-dist[i], i});
			}
		};

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (int i : ed[s]) if (!seen[i])
				relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
			for (int i : red[s]) if (!seen[i])
				relax(i, flow[i][s], -cost[i][s], 0);
		}
		for(int i=0;i<N;i++) pi[i] = min(pi[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
			totflow += fl;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				if (r) flow[p][x] += fl;
				else flow[x][p] -= fl;
		}
		for(int i=0;i<N;i++) for(int j=0;j<N;j++) totcost += cost[i][j] * flow[i][j];
		return {totflow, totcost};
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(pi.begin(),pi.end(), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			for(int i=0;i<N;i++) if (pi[i] != INF)
				for (int to : ed[i]) if (cap[i][to])
					if ((v = pi[i] + cost[i][to]) < pi[to])
						pi[to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

MCMF fluxo(1000);
 
int main(){
 
    string s;cin>>s;
    int t;cin>>t;
    vector<string> strin(t);
    vector<int> maximo(t);
    for(int i=0;i<t;i++){
        cin>>strin[i]>>maximo[i];
    }
 
    vector<int> cont(26);
    for(auto k:s){
        cont[k-'a']++;
    }
 
    int sourc=t+26;
    int snk=sourc+1;
    for (int i=0;i<t;i++){
        fluxo.addEdge(sourc,i,maximo[i],i+1);
    }
    for(int i=0;i<26;i++){
        fluxo.addEdge(t+i,snk,cont[i],0);
    }
    int contador=0;
    for(auto k:strin){
        vector<int> contk(26);
        for (auto k1:k){
            contk[k1-'a']++;
        }
     //   cout<<"st "<<k<<endl;
        for(int i=0;i<26;i++){
            if (contk[i]){
             //   cout<<i<<" "<<contk[i]<<endl;
                fluxo.addEdge(contador,t+i,contk[i],0);
            }
        }
        contador++;
    }
    auto ans=fluxo.maxflow(sourc,snk);
    if (ans.first==s.length())cout<<ans.second<<endl;
    else cout<<-1<<endl;
   // cout<<ans.first<<" "<<ans.second<<endl;
 
    
}
