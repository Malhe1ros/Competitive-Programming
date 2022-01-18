#include <bits/stdc++.h>

using namespace std;

struct BipartiteDSU{
  vector<int> p, sz, color, is_bipartite;
  BipartiteDSU(int n):p(n),sz(n),color(n),is_bipartite(n, 1){
    iota(p.begin(), p.end(), 0);
  }
 
  // FINDS AND UPDATES COLORS + PATH COMPRESSION
  int find(int x){
    int new_par=x;
    int xoor = 0;
    while(p[new_par] != new_par){
      xoor ^= color[new_par]; // connected vertexes are guaranteed to have diff colors
      new_par = p[new_par];
    }
    // cout << "sera?" << endl;
    // if xoor == 1: x and new_par have the same color
    // else: diff colors
    while(p[x] != x){
      int old_color = color[x];
      int old_paar = p[x];
      color[x] = xoor;
      xoor ^= old_color;
      p[x] = new_par;
      x = old_paar;
    }
    return p[x];
  }
 
  int get_color(int x){
    find(x); return color[x];
  }
 
  bool can_onion(int a, int b){
    return (find(a) != find(b)) || (color[a] == color[b]); 
  }
 
  bool onion(int a, int b){
    int pa = find(a), pb = find(b);
    if(pa == pb){
      if(color[a] == color[b]){
        return is_bipartite[pa] = false; // oops
      }else return true; // changes nothing
    }else{
      if(sz[pa] < sz[pb]) swap(pa, pb);
      color[pb] = (color[a] == color[b]);
      p[pb] = pa; sz[pa] += sz[pb];
      is_bipartite[pa] &= is_bipartite[pb];
      return true;
    }
  }
};
 
signed main(){
    
}
