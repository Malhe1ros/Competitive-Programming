#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
#define MAXV 123456
typedef long long ll;
using namespace std;


template<int MAXN>
struct ImplicitSegtree{
  static const int LAZY_NEUTRAL = -1;
  struct Node {
   int val, lazy; // val and lazy values
    int tl, tr; // left and right range
    int l, r; // left and right childs ids
   Node() : val(0), lazy(LAZY_NEUTRAL), l(-1), r(-1) {}
  };

  Node segtree[64 * MAXN];
  int nodeCount = 2;


  int merge(int a, int b){
    return a + b;
  }

  void createChild(int parentNode, int childTl, int childTr, bool isLeft){
    int newNode = getNextId();
    if(isLeft) segtree[parentNode].l = newNode;
    else segtree[parentNode].r = newNode;
    segtree[newNode].tl = childTl;
    segtree[newNode].tr = childTr;
  }

  void maybeCreateChilds(int node){
    int mid = (segtree[node].tl + segtree[node].tr) / 2;
    if (segtree[node].l == -1) {
      createChild(node, segtree[node].tl, mid, true);
    }
    if (segtree[node].r == -1) {
      createChild(node, mid + 1, segtree[node].tr, false);
    }
  }

  inline int getNextId(){ return nodeCount++; }

  ImplicitSegtree(){
    segtree[1].val = 0; segtree[1].lazy = -1;
    segtree[1].tl = 1; segtree[1].tr = 1e9;
    // LAZY_NEUTRAL = -1;
  }

  void push_lazy(int node) {
   if (segtree[node].lazy != LAZY_NEUTRAL) {
    segtree[node].val = segtree[node].lazy;
      maybeCreateChilds(node);
    segtree[segtree[node].l].lazy = segtree[segtree[node].l].tr - segtree[segtree[node].l].tl + 1;
      segtree[segtree[node].r].lazy = segtree[segtree[node].r].tr - segtree[segtree[node].r].tl + 1;
    segtree[node].lazy = LAZY_NEUTRAL;
   }
  }

  void update(int node, int l, int r, int value) {
   push_lazy(node);
   if (l == segtree[node].tl && r == segtree[node].tr) {
    segtree[node].lazy = (segtree[node].tr - segtree[node].tl + 1) * value;
    push_lazy(node);
   } else {
      maybeCreateChilds(node);

      int mid = (segtree[node].tl + segtree[node].tr) / 2;
    if (l > mid) update(segtree[node].r, l, r, value);
    else if (r <= mid) update(segtree[node].l, l, r, value);
    else {
     update(segtree[node].l, l, mid, value);
     update(segtree[node].r, mid + 1, r, value);
    }

    push_lazy(segtree[node].l);
    push_lazy(segtree[node].r);
    segtree[node].val = merge(
        segtree[segtree[node].l].val,
        segtree[segtree[node].r].val
      );
   }
  }

  int query(int node, int l, int r) {
   push_lazy(node);
   if (l == segtree[node].tl && r == segtree[node].tr)
      return segtree[node].val;
   else {
    int mid = (segtree[node].tl + segtree[node].tr) / 2;
      maybeCreateChilds(node);

    if (l > mid) return query(segtree[node].r, l, r);
    else if (r <= mid) return query(segtree[node].l, l, r);
    else return merge(
        query(segtree[node].l, l, mid),
        query(segtree[node].r, mid + 1, r)
      );
   }
  }
};

ImplicitSegtree<MAXV> st;
int main() {
 iostream::sync_with_stdio(false);
 cin.tie(0);
 int m;
 cin >> m;



 int c = 0;
 FOR(_, 0, m) {
  int d, x, y;
  cin >> d >> x >> y;
  if (d == 1) {
   c = st.query(1, x + c, y + c);
   cout << c << '\n';
  } else st.update(1, x + c, y + c, 1);
 }
 return 0;
}
