#include<bits/stdc++.h>
using namespace std;
 
 /*
    Lazy Semi Persistent Max XOR Trie
    It is a XOR Trie that can
    XOR all elements inside the Trie with a value x (lazy)
    Add an element at time T (Semi persistent)
    Queries the element which maximizes xor with x at time T (Max XOR Trie)
 */

//Solves https://oj.uz/problem/view/COCI20_klasika
 
struct Node{
  int size, time_created, lazy;
  array<int,2> c;
  Node(int time, int _size = 0):
    size(_size), time_created(time), lazy(0), c({-1, -1}){}
};
 
struct LazySemiPersMaxXORTrie{
  vector<Node> nodes;
  // root: nodes[0]
  // todos numeros sao armazenados em nos terminais
  // um no terminal pode manter mais de um numero
 
  void propagate_xor(int node, int curr_bit){
    if(get_bit(nodes[node].lazy, curr_bit)){
      swap(nodes[node].c[0], nodes[node].c[1]);
    }
 
    for(int i = 0; i < 2; ++i){
      if(nodes[node].c[i] != -1){
        nodes[nodes[node].c[i]].lazy ^= nodes[node].lazy; 
      }
    }
    nodes[node].lazy = 0;
  }
 
  void xor_all(int x){
    nodes[0].lazy ^= x;
  }
 
 
  LazySemiPersMaxXORTrie(){
    nodes.push_back(Node(-1));
  }
 
  bool get_bit(int x, int i){
    return (x >> i) & 1;
  }
 
  void add(int num, int time, int curr_node = 0, int curr_bit = 31){
    nodes[curr_node].size++;
    nodes[curr_node].time_created = min(nodes[curr_node].time_created, time);
    if(curr_bit == -1) return;
    propagate_xor(curr_node, curr_bit);
 
 
    int b = get_bit(num, curr_bit);
    if(nodes[curr_node].c[b] == -1){
      nodes[curr_node].c[b] = nodes.size();
      nodes.push_back(Node(time));
    }
 
    add(num, time, nodes[curr_node].c[b], curr_bit - 1);
  }
 
  int query_max(int num, int max_perm_time, int curr_node = 0, int curr_bit = 31){
    // want to max (num ^ x)
    if(curr_bit == -1) return 0; // base recursion case
    propagate_xor(curr_node, curr_bit);
 
    assert(nodes[curr_node].size > 0); // cant enter an empty node
 
    int b = !get_bit(num, curr_bit); // target bit (maximize xor)
 
    if((nodes[curr_node].c[b] != -1) && (nodes[nodes[curr_node].c[b]].time_created <= max_perm_time)){
      return query_max(num, max_perm_time, nodes[curr_node].c[b], curr_bit - 1) + (b << curr_bit);
    }else{
      return query_max(num, max_perm_time, nodes[curr_node].c[!b], curr_bit - 1) + ((!b) << curr_bit);
    }
  }
 
};
 
#define MAXN 200010
#define MAXLOG 20
 
vector<int> v[MAXN];
 
int dfs_time = 0;
int xor_until[MAXN];
int sz[MAXN];
int w[MAXN];
int beg[MAXN], en[MAXN], ver[MAXN];
int time_added[MAXN];
 
LazySemiPersMaxXORTrie tries[MAXN];
 
void preprocess_dfs(int x, int p){
  // xor preffix
  xor_until[x] = xor_until[p] ^ w[x];
 
  // sack
  ver[dfs_time] = x;
  beg[x] = dfs_time++;
  sz[x] = 1;
 
  for(auto y : v[x]){
    if(y != p){
      preprocess_dfs(y, x);
      sz[x] += sz[y];
    }
  }
 
  // sack
  en[x] = dfs_time;
}
 
vector<pair<int,int>> queries[MAXN]; // time, val
int ans[MAXN];
 
void solve(int x){
  int heavy_child = -1;
  int max_size = -1;
 
  for (auto k : v[x]){
    if (sz[k] > max_size){
      max_size = sz[k];
      heavy_child = k;
    }
  }
 
  
  for (auto k : v[x]) solve(k);
 
  if(heavy_child != -1){
    swap(tries[x], tries[heavy_child]);
    tries[x].xor_all(w[heavy_child]);
 
    for (auto k : v[x]){
      tries[k].nodes.clear();
      if (k != heavy_child){
        for(int it = beg[k]; it < en[k]; ++it){
          tries[x].add(xor_until[ver[it]] ^ xor_until[x], time_added[ver[it]]);
        }
      }
    }
  }
 
  tries[x].add(0, time_added[x]);
  for(auto [t, a] : queries[x]){
    ans[t] = a ^ tries[x].query_max(a, t);
  }
}
 
int main(){
  memset(ans, -1, sizeof ans);
 
  int next_node = 2;
  int n; cin >> n;
  
  vector<pair<int,pair<int,int>>> q;
  for(int i = 0; i < n; ++i){
    string s; cin >> s;
    if(s[0] == 'A'){
      int par, weight; cin >> par >> weight;
      time_added[next_node] = i;
      w[next_node] = weight;
      v[par].push_back(next_node);
      next_node++;
    }else{
      int start, subtree; cin >> start >> subtree;
      q.push_back({i, {start, subtree}});
    }
  }
 
  preprocess_dfs(1, 0);
 
  for(auto [i, ab] : q){
    auto [start, subtree] = ab;
    int val = xor_until[start] ^ xor_until[subtree];
    queries[subtree].push_back({i, val});
  }
  q.clear();
  solve(1);
 
  for(int i = 0; i < MAXN; ++i){
    if(ans[i] != -1) cout << ans[i] << "\n";
  }
}
