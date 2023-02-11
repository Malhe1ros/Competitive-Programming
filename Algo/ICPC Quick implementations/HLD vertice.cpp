#include<bits/stdc++.h>
using namespace std;

//#define int long long
#define MAXN 200010


struct Node{
  int cnt[7];
  Node(){
    memset(cnt, 0, sizeof cnt);
  }
  Node operator+(Node n){
    Node ret;
    for(int i = 0; i < 7; ++i){
      ret.cnt[i] = cnt[i] + n.cnt[i];
    }
    return ret;
  }
};

namespace seg {
	Node seg[4*MAXN];
    int lazy[4*MAXN];
	int n;
    const Node NEUTRAL;

	Node build(int p=1, int l=0, int r=n-1) {
		lazy[p] = -1;
		if (l == r) return seg[p] = NEUTRAL;
		int m = (l+r)/2;
		return seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
	}
	void init(int n2) {
		n = n2;
		build();
	}
	void prop(int p, int l, int r) {
		if(lazy[p] == -1) return;
        memset(seg[p].cnt, 0, sizeof seg[p].cnt);
        seg[p].cnt[lazy[p]] = r - l + 1;
		if (l != r) lazy[2*p] = lazy[p], lazy[2*p+1] = lazy[p];
		lazy[p] = -1;
	}
	Node query(int lq, int rq, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (lq <= l && r <= rq) return seg[p];
		if (rq < l || r < lq) return NEUTRAL;
		int m = (l+r)/2;
		return query(lq, rq, 2*p, l, m) + query(lq, rq, 2*p+1, m+1, r);
	}
	void update(int lu, int ru, int x, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if(lu <= l && r <= ru){
			lazy[p] = x;
			prop(p, l, r);
		}else if(ru >= l && r >= lu){
      int m = (l+r)/2;
      update(lu, ru, x, 2*p, l, m); update(lu, ru, x, 2*p+1, m+1, r);
      seg[p] = seg[2*p] +	seg[2*p+1];
    }
	}
};

namespace hld {
	vector<int> g[MAXN];
	int pos[MAXN], sz[MAXN];
	int sobe[MAXN], pai[MAXN];
	int h[MAXN], v[MAXN], t;
    int d[MAXN];

    void add_edge(int a,int b){
        hld::g[a].push_back(b);
        hld::g[b].push_back(a);
    }

	void build_hld(int k, int p = -1, int f = 1) {
		pos[k] = t++; sz[k] = 1;
        if(p != -1) d[k] = d[p] + 1;
		for (auto& u : g[k]) if (u != p) {
			pai[u] = k;
			h[u] = (u == g[k][0] ? h[k] : u);
			build_hld(u, k, f); sz[k] += sz[u];

			if (sz[u] > sz[g[k][0]] or g[k][0] == p)
				swap(u, g[k][0]);
		}
		if (p*f == -1) build_hld(h[k] = k, -1, t = 0);
	}
	void build(int root = 0) {
		t = 0;
        d[root] = 0;
		build_hld(root);
		seg::init(t);
	}
	Node query_path(int a, int b) {
		if (a == b) return Node();
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return seg::query(pos[b]+1, pos[a]);
		return seg::query(pos[h[a]], pos[a]) + query_path(pai[h[a]], b);
	}
	void update_path(int a, int b, int x) {
		if (a == b) return;
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return (void)seg::update(pos[b]+1, pos[a], x);
		seg::update(pos[h[a]], pos[a], x); update_path(pai[h[a]], b, x);
	}
	int lca(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
}

vector<string> S;
map<string,int> M;
int get_id(string s){
  if(M.count(s) == 0){
    M[s] = M.size();
    S.push_back(s);
  }
  return M[s];
}

int32_t main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
  int n; cin >> n;
  for(int i = 0; i < n - 1; ++i){
    int a, b; cin >> a >> b;
    hld::add_edge(a,b);
  }
  hld::build();

  get_id("red");
  get_id("orange");
  get_id("yellow");
  get_id("green");
  get_id("blue");
  get_id("indigo");
  get_id("violet");

  vector<int> ans(7);
  int q; cin >> q;
  while(q--){
    int a, b; cin >> a >> b;
    string s; cin >> s;
    int sid = get_id(s);

    int num = hld::d[a] + hld::d[b] - 2 * hld::d[hld::lca(a, b)] + 1; //quantos tem no path?
    auto x = hld::query_path(a, b);
    ans[sid] += num - x.cnt[sid] - 1;
    hld::update_path(a, b, sid);
  }
  for(int i = 0; i < 7; ++i){
    cout << S[i] << " " << ans[i] << endl;
  }
}
