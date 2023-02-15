#include <bits/stdc++.h>

using namespace std;

#define T long long //CUIDADO


const int MAXN = 200000;//quantidade de nós
const int MIN = -1e9;
struct Line {
  T m, b;
  Line(T _m=0, T _b=MIN):m(_m),b(_b){}
  T operator()(T x) { return m * x + b; }
} seg[MAXN];
 
T l[MAXN], r[MAXN];
int l_ptr[MAXN], r_ptr[MAXN];
int next_node = 0;
 
int build_node(T L, T R){
  int id = next_node++;
  l[id] = L, r[id] = R;
  seg[id] = Line();
  return id;
}
 
int get_node(int node, bool is_l){
  T m = (l[node] + r[node]) / 2;
  if(is_l){
    if(!l_ptr[node]) 
      l_ptr[node] = build_node(l[node], m);
    return l_ptr[node];
  }else{
    if(!r_ptr[node]) 
      r_ptr[node] = build_node(m, r[node]);
    return r_ptr[node];
  }
}
 
void insert(int node, Line f){
  T m = (l[node] + r[node]) / 2;
  bool better_at_m = f(m) > seg[node](m);
  if(better_at_m) swap(f, seg[node]);
 
  bool better_at_l = f(l[node]) > seg[node](l[node]);
  bool better_at_r = f(r[node]) > seg[node](r[node]);
 
  if(!better_at_l && !better_at_r) return;
  if(better_at_l){
    insert(get_node(node, 1), f);
  }else{
    insert(get_node(node, 0), f);
  }
}
 
T query(int node, T x){
  T m = (l[node] + r[node]) / 2;
  T ans = seg[node](x);
  if(x < m){
    if(l_ptr[node]) ans = max(ans, query(l_ptr[node], x));
  }else if(r_ptr[node]) ans = max(ans, query(r_ptr[node], x));
  return ans;
}
#define int long long
int32_t main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int root = build_node(-1e9-10, 1e9+10);//VE AQUI
	
    int n, m; cin >> n >> m;
  vector<int> b(n);
  for(auto &x : b) cin >> x;
  sort(b.rbegin(), b.rend());
 
  for(int i = 0; i < n; ++i){
    insert(root, Line(i + 1, (i + 1) * b[i]));
  }
 
  for(int i = 0; i < m; ++i){
    int x; cin >> x;
    cout << query(root, x) << " ";
  }
  cout << "\n";
}
