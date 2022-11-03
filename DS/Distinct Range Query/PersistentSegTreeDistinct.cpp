#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int)x.size()

const int MAXN = 1e5+10;
const int MAXLGN = 20;
 
int n, q;
int tree[MAXN];
int cant;
std::map<int, int> pos;
 
struct node {
  int val, L, R, size;
} buff[2 * MAXN * MAXLGN];
 
int build(int f, int t) {
  if (f > t) return 0; 
  int idx = ++cant;
  int m = (f + t) >> 1;
  buff[idx] = (node){ m, build(f, m - 1), build(m + 1, t), 0 };
  return idx;
}
 
int update(int x, int val, int amount) { 
  if (x == 0) return 0;
  int idx = ++cant;
  int L = buff[x].L;
  int R = buff[x].R;
  if (val < buff[x].val) L = update(L, val, amount);
  if (val > buff[x].val) R = update(R, val, amount);
  buff[idx] = (node){ buff[x].val, L, R, buff[x].size + amount };
  return idx;
}
 
int query(int x, int val) {
  if (val < buff[x].val)
    return query(buff[x].L, val) + buff[x].size -  buff[buff[x].L].size; 
  if (val > buff[x].val)
    return query(buff[x].R, val);
  return buff[x].size - buff[buff[x].L].size;
}


int distinct(int l,int r){
  return query(tree[r],l);
}

int findNext(int beg,int maxi){
  int l = beg;
  int r = n+1;
  int melhor = beg;
  while(l<r){
    int mid = (l+r)/2;
    if(distinct(beg,mid)<=maxi){
       melhor=mid;
       l=mid+1;
    }
    else{
      r=mid;
    }
  }
  return melhor+1;
}

int solve(int maxi){
  int l=0;
  int tot=0;
  while(l<=n){
    l = findNext(l,maxi);
    tot++;
  }
  return tot;
}

signed main(){
  scanf("%d", &n);
  tree[0] = build(1, n);
  for (int i = 1; i <= n; i++ ) {
    int x, posx;
    scanf("%d", &x);
    posx = pos[x];
    if (posx != 0 ) {
      tree[i] = update(update(tree[i - 1], posx, -1), i, +1);
    } else {
      tree[i] = update(tree[i - 1], i, +1);
    }
    pos[x] = i;
  } 
  
  
  
  for(int i=1;i<=n;i++){
    printf("%d ",solve(i));
  }

  cout<<'\n';
}
