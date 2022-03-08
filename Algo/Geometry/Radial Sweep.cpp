#include<bits/stdc++.h>
using namespace std;

struct PV{
  int x, y;

  PV(){x = 0, y = 0;}
  PV(int a, int b){
    x = a, y = b;
  }

  int cross(PV p){
    return x * p.y - p.x * y;
  }

  PV operator-(PV p){
    return {x - p.x, y - p.y};
  }

  bool operator<(const PV &p) const{
    return make_pair(x, y) < make_pair(p.x, p.y);
  }

  void normalize(){
    if(x == 0 && y == 0) return;
    else if(x == 0) y /= abs(y);
    else if(y == 0) x /= abs(x);
    else{
      int g = __gcd(abs(x), abs(y));
      x /= g, y /= g;
    } 
  }
};

bool half(PV &a) { // 1 e 2 quadrantes
    PV p = a;
    assert(p.x != 0 || p.y != 0); // the argument of (0,0) is undefined
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

bool cmp(PV &a, PV &b){
    if(half(a) == half(b)){
        int temp = (a).cross(b);
        return temp > 0;
    }else{
        return half(a) < half(b);
    }
}

int32_t main(){
    int n; cin >> n; n--;
    int m = n;

    int xc, yc; cin >> xc >> yc;
    PV center(xc,yc);
    
    map<PV, int> count_coord;
    vector<PV> v; // will hold points different from pivot
    int eqs = 0; // num points equal to pivot
    int tot = 0; // num points dif from pivot
    for(int i = 0; i < n; ++i){
      int x, y; cin >> x >> y;
      // shifting using pivot for normalizaiton (pivot is now (0,0))
      x -= center.x, y -= center.y;
      if(x == 0 && y == 0) eqs++;
      else{
        PV p(x, y);
        p.normalize();
        if(count_coord.count(p) == 0){
          v.push_back(p);
          count_coord[p] = 0;
        }
        count_coord[p]++, tot++;
      }
    }
    sort(v.begin(), v.end(), cmp);

    if(v.empty()){
      cout << "1 1\n";
      return 0;
    }

    int mais_maiores = 0;
    int menos_maiores = m;

    int l = 0, r = 0;
    int inside_window = count_coord[v[l]];
    while(l < v.size()){
      while(true){
        int next_r = (r + 1) % v.size();
        if(next_r == l || v[next_r].cross(v[l]) > 0) break;
        inside_window += count_coord[v[r = next_r]];
      }

      int l_points = count_coord[v[l]]; // cnt points in v[l] direction
      int r_points = count_coord[v[r]]; // cnt points in v[r] direction

      int in_line = l_points;
      // if v[l] and v[r] are colinear directions, v[r] are also inside the sweep line
      if(v[l].cross(v[r]) == 0 && l != r) in_line += r_points;

      // pivot (and equal points) not included
      int a = inside_window - in_line; // inside sliding window
      int b = in_line; // in line
      int c = tot - (a + b); // outside sliding window

      // querying
      // problem: specific quadrants
      if(v[l].x >= 0 && v[l].y <= 0){
        mais_maiores = max(mais_maiores, a + b + eqs);
        menos_maiores = min(menos_maiores, a);
      }else if(v[l].x <= 0 && v[l].y >= 0){
        mais_maiores = max(mais_maiores, c + b + eqs);
        menos_maiores = min(menos_maiores, c);
      }

      if(l + 1 == v.size()) break;
      // walking r together for guarantee window integrity
      if(r == l) inside_window += count_coord[v[++r]];
      inside_window -= count_coord[v[l++]];
    }

    cout << menos_maiores + 1 << " " << mais_maiores + 1 << "\n";
}
