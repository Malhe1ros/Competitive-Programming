#include<bits/stdc++.h>
using namespace std;
 
#define LOG_MAXN 19
#define MAXN 1000010

//solves https://codeforces.com/contest/86/problem/D
//written by pauloamed

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) return 0;
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}
 
struct Query {
	int l, r, idx; // 1 indexado
	int64_t ord;
 
	inline void calcOrder() {
		ord = gilbertOrder(l, r, LOG_MAXN, 0);
	}
};
 
#define ll long long
ll curr;
vector<int> v;
int cnt[MAXN];
 
int walkRLeft(int r){
  // estou tirando o v[r]
  ll x = 2 * (cnt[v[r]]--) - 1;
  curr -= x * v[r];
  return r - 1;
}
 
int walkRRight(int r){
  // estou adicionando v[r + 1]
  ll x = 2 * (cnt[v[++r]]++) + 1;
  curr += x * v[r];
  return r;
}
 
int walkLLeft(int l){
  // estou adicionando v[l - 1]
  ll x = 2 * (cnt[v[--l]]++) + 1;
  curr += x * v[l];
  return l;
}
 
int walkLRight(int l){
  // estou tirando o v[l]
  ll x = 2 * (cnt[v[l]]--) - 1;
  curr -= x * v[l];
  return l + 1;
}
 
 
 
int main(){
  iostream::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q; cin >> n >> q; v = vector<int>(n); for(auto &x : v) cin >> x;
  vector<Query> qs(q);
  for(int i = 0; i < q; ++i){
    cin >> qs[i].l >> qs[i].r;
    qs[i].idx = i;
    qs[i].calcOrder();
  }
  sort(qs.begin(), qs.end(), [&](Query &a, Query &b){return a.ord < b.ord;});
  vector<ll> ans(q);
  int lastL = 0, lastR = 0;
  curr = v[0]; cnt[v[0]]++;
  for(auto q : qs){
    q.l--; q.r--;
    // first expand range
    while(lastR < q.r) lastR = walkRRight(lastR);
    while(lastL > q.l) lastL = walkLLeft(lastL);
    // then restrict
    while(lastR > q.r) lastR = walkRLeft(lastR);
    while(lastL < q.l) lastL = walkLRight(lastL);
    ans[q.idx] = curr;
  }
  for(auto x : ans) cout << x << "\n";
}
