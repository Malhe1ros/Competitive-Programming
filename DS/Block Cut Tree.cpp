#include<bits/stdc++.h>
using namespace std;

struct block_cut_tree {
	vector<vector<int>> g, blocks, tree;
	vector<vector<pair<int, int>>> edgblocks;
	stack<int> s;
	stack<pair<int, int>> s2;
	vector<int> id, art, pos;
    int pontes = 0;
    int arts = 0;
    int maxs = 0;
	
	block_cut_tree(vector<vector<int>> g_) : g(g_) {
		int n = g.size();
		id.resize(n, -1), art.resize(n), pos.resize(n);
		build();

        for(int i = 0; i < n; ++i){
            if(art[i] >= 1) arts++;
        }
        for(auto &x : edgblocks) maxs = max(maxs, (int) x.size());
	}


	int dfs(int i, int& t, int p = -1) {
		int lo = id[i] = t++;
		s.push(i);	
		
		if (p != -1) s2.emplace(i, p);
		for (int j : g[i]) if (j != p and id[j] != -1) s2.emplace(i, j);
		
		for (int j : g[i]) if (j != p) {
			if (id[j] == -1) {
				int val = dfs(j, t, i);
				lo = min(lo, val);

				if (val >= id[i]) {
					art[i]++;
					blocks.emplace_back(1, i);
					while (blocks.back().back() != j) 
						blocks.back().push_back(s.top()), s.pop();

					edgblocks.emplace_back(1, s2.top()), s2.pop();
					while(edgblocks.back().back() != pair(j, i))
						edgblocks.back().push_back(s2.top()), s2.pop();
				}
				if (val > id[i]) pontes++;
			}
			else lo = min(lo, id[j]);
		}
		
		if (p == -1 and art[i]) art[i]--;
		return lo;
	}

	void build() {
		int t = 0;
		for (int i = 0; i < g.size(); i++) if (id[i] == -1) dfs(i, t, -1);
		
		tree.resize(blocks.size());
		for (int i = 0; i < g.size(); i++) if (art[i]) 
			pos[i] = tree.size(), tree.emplace_back();

		for (int i = 0; i < blocks.size(); i++) for (int j : blocks[i]) {
			if (!art[j]) pos[j] = i;
			else tree[i].push_back(pos[j]), tree[pos[j]].push_back(i);
		}
	}
};


int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        int n, m; cin >> n >> m;
        vector<vector<int>> g(n, vector<int>());
        for(int i = 0; i < m; ++i){
            int a,b; cin >> a >> b; a--, b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        block_cut_tree bct(g);
        cout << bct.arts << " " << bct.pontes << " ";
        int gg = __gcd((int)bct.blocks.size(), bct.maxs);
        cout << bct.blocks.size() / gg << " " << bct.maxs / gg << endl;
    }
}
