#include <bits/stdc++.h>
 
using namespace std;
struct Treap{
  int el_val;
  long long tree_val;
  int size, pri;
  Treap* l,*r;
  bool do_rev;
 
  Treap(int x){
    size = 1;
    el_val = tree_val = x;
    pri=rand();
    l=r=NULL;
    do_rev = false;
  }
 
};
 
void rev(Treap *t){
  if(t) t->do_rev = t->do_rev ^ 1;
}
 
 
void maybe_apply(Treap *t){
  if(t && t->do_rev){
    swap(t->l, t->r);
    rev(t->l); rev(t->r);
    t->do_rev = false;
  }
}
 
void updt_info(Treap* x){
  maybe_apply(x);
  x->size=1;
  x->tree_val=x->el_val;
  if(x->l!=NULL){
    x->size+=x->l->size;
    x->tree_val+=x->l->tree_val;
  }
  if(x->r!=NULL){
    x->size+=x->r->size;
    x->tree_val+=x->r->tree_val;
  }
}

//builds the Treap in O(n);
void heapify (Treap* t) {
  if (!t) return;
  Treap* max = t;
  if(t->l != NULL && t->l->pri > max->pri) max = t->l;
  if(t->r != NULL && t->r->pri > max->pri) max = t->r;
  if(max != t){
    swap(t->pri, max->pri);
    heapify(max);
  }
}

Treap* build(vector<int> &a, int l, int r) {
  // Construct a treap on values {a[0], a[1], ..., a[n - 1]}
  if (r <= l) return NULL;
  int mid = (l + r) / 2;
  Treap* t = new Treap(a[mid]);
  if(r - l > 1){
    t->l = build(a, l, mid);
    t->r = build(a, mid + 1, r);
    heapify(t);
  }
  updt_info(t);
  return t;
}

 
int key(Treap* x){
  maybe_apply(x);
  if(x->l!=NULL) return x->l->size;
  return 0;
}
 
 
void split(Treap* x, Treap* &ret_left, Treap* &ret_right, int u){
  maybe_apply(x);
  if(x==NULL){
    ret_left = ret_right = NULL;
    return;
  }
 
  if(key(x) < u){
    split(x->r, x->r, ret_right, u-key(x)-1);
    ret_left = x;
  }else{
    split(x->l, ret_left, x->l, u);   
    ret_right = x;
  }
  updt_info(x);
}
 
pair<Treap*,Treap*> split(Treap* x, int u){
  Treap* low = NULL, *high = NULL;
  split(x, low, high, u);
  return {low, high};
}
 
void merge(Treap* a, Treap* b, Treap* &ret){
  maybe_apply(a); maybe_apply(b);
  if(a == NULL) {ret = b; return;}
  if(b == NULL) {ret = a; return;}
 
  if(a->pri > b->pri){
    merge(a->r, b, a->r);
    updt_info(a);
    ret = a;
  }else{
    merge(a, b->l, b->l);
    updt_info(b);
    ret = b;
  }
}
 
Treap* merge(Treap *a, Treap *b){
  Treap* x = NULL;
  merge(a, b, x);
  return x;
}
 
tuple<Treap*, Treap*, Treap*> split(Treap *t, int l, int r){
  int size = r - l + 1;
  auto [left, x_right] = split(t, l);
  auto [x, right] = split(x_right, size);
 
  return {left, x, right};
}
 
long long query(Treap* &t,int l,int r){
  //cout<<l<<" ",
  auto [left, x, right] =split(t,l,r);
  long long val=x->tree_val;
  t=merge(merge(left, x), right);
  return val;
}
 
Treap* rev(Treap *t, int l, int r){ // [l;r]
  auto [left, x, right] = split(t, l, r);
  rev(x);
  return merge(merge(left, x), right);
}
 
 
Treap* insert_kth(Treap* t, int k, int u){
  // inserted value will be the k-th
  auto pont = new Treap(u);
  auto [left, right] = split(t, k);
  return merge(merge(left,pont), right);
}
 
Treap* erase_kth(Treap* t, int k){
  auto [left, x_right] = split(t, k);
  auto [x, right] = split(x_right, 1);
  delete x;
  return merge(left, right);
}
 
 
signed main(){
  cin.tie(NULL)->sync_with_stdio(false);
  int n, q; cin >> n >> q;
  vector<int> v(n);
  for(int i = 1; i <= n; ++i){
    cin>>v[i-1];
  }
  Treap* root = build(v, 0, n);
 
  while(q--){
    int a;cin>>a;
    
    int l, r; cin >> l >> r; l--, r--;
    if(a==1)root = rev(root, l, r);
    else cout<<query(root,l,r)<<'\n';
  }
 
}
