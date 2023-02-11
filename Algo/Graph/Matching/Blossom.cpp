#include <bits/stdc++.h>
using namespace std;


const int MAX = 2010;
vector<int> g[MAX];
int match[MAX]; // match[i] = com quem i esta matchzado ou -1
int n, pai[MAX], base[MAX], vis[MAX]; //tem que setar o n
queue<int> q;

void contract(int u, int v, bool first = 1) {
	static vector<bool> bloss;
	static int l;
	if (first) {
		bloss = vector<bool>(n, 0);
		vector<bool> teve(n, 0);
		int k = u; l = v;
		while (1) {
			teve[k = base[k]] = 1;
			if (match[k] == -1) break;
			k = pai[match[k]];
		}
		while (!teve[l = base[l]]) l = pai[match[l]];
	}
	while (base[u] != l) {
		bloss[base[u]] = bloss[base[match[u]]] = 1;
		pai[u] = v;
		v = match[u];
		u = pai[match[u]];
	}
	if (!first) return;
	contract(v, u, 0);
	for (int i = 0; i < n; i++) if (bloss[base[i]]) {
		base[i] = l;
		if (!vis[i]) q.push(i);
		vis[i] = 1;
	}
}

int getpath(int s) {
	for (int i = 0; i < n; i++) base[i] = i, pai[i] = -1, vis[i] = 0;
	vis[s] = 1; q = queue<int>(); q.push(s);
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int i : g[u]) {
			if (base[i] == base[u] or match[u] == i) continue;
			if (i == s or (match[i] != -1 and pai[match[i]] != -1))
				contract(u, i);
			else if (pai[i] == -1) {
				pai[i] = u;
				if (match[i] == -1) return i;
				i = match[i];
				vis[i] = 1; q.push(i);
			}
		}
	}
	return -1;
}

int blossom() {
	int ans = 0;
	memset(match, -1, sizeof(match));
	for (int i = 0; i < n; i++) if (match[i] == -1)
		for (int j : g[i]) if (match[j] == -1) {
			match[i] = j;
			match[j] = i;
			ans++;
			break;
		}
	for (int i = 0; i < n; i++) if (match[i] == -1) {
		int j = getpath(i);
		if (j == -1) continue;
		ans++;
		while (j != -1) {
			int p = pai[j], pp = match[p];
			match[p] = j;
			match[j] = p;
			j = pp;
		}
	}
	return ans;
}
const int maxn  = 1e5+10;
int gamb[maxn];
signed main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int m;cin>>n>>m;
    vector<int>v;
    for(int i = 0;i<m;i++){
        int a;cin>>a;
        v.push_back(a);
    }
    vector<vector<int>> caras(n);
    for(int i = 0;i<n;i++){
        int x;cin>>x;
        for(int j = 0;j<x;j++){
            int a;cin>>a;
            caras[i].push_back(a);
        }

    }
    auto pode = [&](int a,int b){
        for(auto k:caras[a])gamb[k]++;
        for(auto k:caras[b])gamb[k]++;
        bool dm = 1;
        for(auto k:v){
            if(gamb[k]==0)dm = 0;
        }
        for(auto k:caras[a])gamb[k]--;
        for(auto k:caras[b])gamb[k]--;
        return dm;
    };
    for(int i = 0;i<n;i++){
        for(int j = i+1;j<n;j++)if(pode(i,j)){
            g[i].push_back(j);
            g[j].push_back(i);
            //cout<<i<<" "<<j<<endl;
        }
    }
    auto ans = blossom();
    //cout<<ans<<endl;
    if(2*ans==n){
        cout<<"SIM\n";
    }
    else cout<<"NAO\n";
}
