#include <bits/stdc++.h>


using namespace std;

const int MAX = 2e5+10;

namespace lca{
    vector<int> grafo[MAX];
    int pos[MAX], h[MAX], sz[MAX];
    int pai[MAX], t;
    int ddepth[MAX];

    void build(int k, int p = -1, int f = 1,int d = 0) {
        pos[k] = t++; sz[k] = 1;
        ddepth[k] = d;
        for (int& i : grafo[k]) if (i != p) {
            pai[i] = k;
            h[i] = (i == grafo[k][0] ? h[k] : i);
            build(i, k, f,d+1); sz[k] += sz[i];
            
            if (sz[i] > sz[grafo[k][0]] or grafo[k][0] == p) swap(i, grafo[k][0]);
        }
        if (p*f == -1) t = 0, h[k] = k, build(k, -1, 0, d+1);
    }

    int lca(int a, int b) {
        if (pos[a] < pos[b]) swap(a, b);
        return h[a] == h[b] ? b : lca(pai[h[a]], b);
    }

    bool anc(int a, int b) {
        return pos[a] <= pos[b] and pos[b] <= pos[a]+sz[a]-1;
    }

    int dist(int a,int b){
        return ddepth[a]+ddepth[b]-2*ddepth[lca(a,b)];
    }
};

vector<pair<int, int>> virt[MAX];//first é pra onde, second é distancia

int build_virt(vector<int> v) {
	auto cmp = [&](int i, int j) { return lca::pos[i] < lca::pos[j]; };
	sort(v.begin(), v.end(), cmp);
	for (int i = v.size()-1; i; i--) v.push_back(lca::lca(v[i], v[i-1]));
	sort(v.begin(), v.end(), cmp);
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i = 0; i < v.size(); i++) virt[v[i]].clear();
	for (int i = 1; i < v.size(); i++) virt[lca::lca(v[i-1], v[i])].clear();
	for (int i = 1; i < v.size(); i++) {
		int parent = lca::lca(v[i-1], v[i]);
		int d = lca::dist(parent, v[i]);
		virt[parent].emplace_back(v[i], d);
	}
	return v[0];
}

void dfs(int u){
    cout<<u<<": "<<endl;
    for(auto k:virt[u]){
        cout<<k.first<<" "<<k.second<<endl;
    }
    for(auto k:virt[u]) dfs(k.first);
}

signed main(){
    int n;cin>>n;
    for(int i = 0;i<n-1;i++){
        int a,b;cin>>a>>b;a--;b--;
        lca::grafo[a].push_back(b);
        lca::grafo[b].push_back(a);
    }
    int k;cin>>k;
    vector<int> v(k);
    for(int i = 0;i<k;i++){
        cin>>v[i];
        v[i]--;
    }
    lca::build(0);
    int r = build_virt(v);
    dfs(r);
}
