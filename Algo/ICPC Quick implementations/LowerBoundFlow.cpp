// Dinic
// Pego de brunomaletta
// O(min(m * max_flow, n^2 m))
// Grafo com capacidades 1 -> O(sqrt(n)*m)


struct dinic {
	const bool scaling = false; // com scaling -> O(nm log(MAXCAP)),
	int lim;                    // com constante alta
	struct edge {
		int to, cap, rev, flow; // para, capacidade, id da reversa, fluxo
		bool res; // se a aresta eh residual
		edge(int to_, int cap_, int rev_, bool res_)
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
	};

	vector<vector<edge>> g;
	vector<int> lev, beg;
	ll F;
	dinic(int n) : g(n), F(0) {}

	void add(int a, int b, int c) { // de a pra b com cap. c
		g[a].push_back(edge(b, c, g[b].size(), false));
		g[b].push_back(edge(a, 0, g[a].size()-1, true));
	}
	bool bfs(int s, int t) {
		lev = vector<int>(g.size(), -1); lev[s] = 0;
		beg = vector<int>(g.size(), 0);
		queue<int> q; q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto& i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				if (scaling and i.cap - i.flow < lim) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	int dfs(int v, int s, int f = INF){
		if (!f or v == s) return f;
		for (int& i = beg[v]; i < g[v].size(); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, s, min(f, e.cap - e.flow));
			if (!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll max_flow(int s, int t) {
		for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
			while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
		return F;
	}
	vector<pair<int, int> > get_cut(int s, int t) {
		max_flow(s, t);
		vector<pair<int, int> > cut;
		vector<int> vis(g.size(), 0), st = {s};
		vis[s] = 1;
		while (st.size()) {
			int u = st.back(); st.pop_back();
			for (auto e : g[u]) if (!vis[e.to] and e.flow < e.cap)
				vis[e.to] = 1, st.push_back(e.to);
		}
		for (int i = 0; i < g.size(); i++) for (auto e : g[i])
			if (vis[i] and !vis[e.to] and !e.res) cut.push_back({i, e.to});
		return cut;
	}
};


// Max flow com lower bound nas arestas
// pego de brunomaletta
// add(a, b, l, r):
// 	adiciona aresta de a pra b, onde precisa passar f de fluxo, l <= f <= r
// add(a, b, c):
// 	adiciona aresta de a pra b com capacidade c
//
// Mesma complexidade do Dinic

struct lb_max_flow : dinic {
	vector<int> d;
	lb_max_flow(int n) : dinic(n + 2), d(n, 0) {}
	void add(int a, int b, int l, int r) {
		d[a] -= l;
		d[b] += l;
		dinic::add(a, b, r - l);
	}
	void add(int a, int b, int c) {
		dinic::add(a, b, c);
	}
	bool has_circulation() {
		int n = d.size();

		ll cost = 0;
		for (int i = 0; i < n; i++) {
			if (d[i] > 0) {
				cost += d[i];
				dinic::add(n, i, d[i]);
			} else if (d[i] < 0) {
				dinic::add(i, n+1, -d[i]);
			}
		}

		return (max_flow(n, n+1) == cost);
	}
	bool has_flow(int src, int snk) {
		dinic::add(snk, src, INF);
		return has_circulation();
	}
};
