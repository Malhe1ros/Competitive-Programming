#include<bits/stdc++.h>
using namespace std;

#define int long long
#define LOG_MAXN 20
#define MAXN 1000010

//solves https://codeforces.com/contest/877/problem/F

inline int64_t HilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) return 0;
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = HilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}
 
struct Query {
	int l, r, idx; 
	int64_t ord;
 
	inline void calcOrder() {
		ord = HilbertOrder(l, r, LOG_MAXN, 0);
	}
};
 

vector<int> v;
 
int l=0;
int r=-1;//i have the answer calculated from l to r;
int pref[MAXN];
int resp=0;
unordered_map<int,int> cnt;
int k;
void walkRLeft(){//removing r;
  cnt[pref[r]]--;
  resp-=cnt[pref[r]-k];
  
  r--;
}
 
void walkRRight(){//adding r;
  r++;
  resp+=cnt[pref[r]-k];
  cnt[pref[r]]++;

}
 
void walkLLeft(){//adding l;
  l--;
  resp+=cnt[pref[l]+k];
  cnt[pref[l]]++;

}
 
void walkLRight(){//removing l;
  cnt[pref[l]]--;
  resp-=cnt[pref[l]+k];
  
  l++;
}
 
 
 
signed main(){
  iostream::sync_with_stdio(false);
  cin.tie(NULL);
  int n; cin >> n>>k;
   v = vector<int>(n); 
   vector<int>quem=vector<int>(n);
   
   for(auto &x : quem) cin >> x;
   for(auto &x : v)cin>>x;
   for(int i=0;i<n;i++){
     if (quem[i]==1){
       pref[i+1]=pref[i]+v[i];
     }
     else{
        pref[i+1]=pref[i]-v[i];
     }
   }
  
  
  int q;cin>>q;
  vector<Query> qs(q);
  for(int i = 0; i < q; ++i){
    cin >> qs[i].l >> qs[i].r;
    qs[i].l--;
    qs[i].idx = i;
    qs[i].calcOrder();
  }
  sort(qs.begin(), qs.end(), [&](Query &a, Query &b){return a.ord < b.ord;});
  vector<int> ans(q);

  for(auto q : qs){
    // first expand range
    while(r < q.r) walkRRight();
    while(l > q.l) walkLLeft();
    // then restrict
    while(r > q.r) walkRLeft();
    while(l < q.l) walkLRight();
    ans[q.idx] = resp;
  }
  for(auto x : ans) cout << x << "\n";
}
