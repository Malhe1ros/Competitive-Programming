#include<bits/stdc++.h>
using namespace std;
/*
	returns x such that a^x = b (mod)
	guarantees existance;
*/
#define ll long long
const int INF=1e9+10;
int dlog(int b, int a, int m) {
	if (a == 0) return b ? -1 : 1; // caso nao definido

	a %= m, b %= m;
	int k = 1, shift = 0;
	while (1) {
		int g = __gcd(a, m);
		if (g == 1) break;

		if (b == k) return shift;
		if (b % g) return -1;
		b /= g, m /= g, shift++;
		k = (ll) k * a / g % m;
	}

	int sq = sqrt(m)+1, giant = 1;
	for (int i = 0; i < sq; i++) giant = (ll) giant * a % m;

	vector<pair<int, int>> baby;
	for (int i = 0, cur = b; i <= sq; i++) {
		baby.emplace_back(cur, i);
		cur = (ll) cur * a % m;
	}
	sort(baby.begin(), baby.end());

	for (int j = 1, cur = k; j <= sq; j++) {
		cur = (ll) cur * giant % m;
		auto it = lower_bound(baby.begin(), baby.end(), make_pair(cur, INF));
		if (it != baby.begin() and (--it)->first == cur)
			return sq * j - it->second + shift;
	}

	return -1;
}

signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    int t;cin>>t;
	while(t--){
		int a,b,mod;cin>>a>>b>>mod;
		cout<<dlog(b,a,mod)<<'\n';
	}
    
}
