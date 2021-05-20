#include <bits/stdc++.h>

//solves http://www.usaco.org/index.php?page=viewproblem2&cpid=764
/*
floyd algorithm (hare and tortoise) finds all cycles in functional graphs in O(V) time
[i rather use a dfs and hash but it's a nice algorithm to have in mind]
*/

using namespace std;
const int maxn=2e5+10;

vector<bool> isciclo(maxn,false);
int pai[maxn];
vector<bool> visto(maxn,false);
void floyd(int ind){
  int tort=ind;
  int hare=pai[ind];
  if (visto[hare]){
    visto[ind]=true;
    return;
  }
  while(tort!=hare){
    if (visto[tort]){
      while(ind!=tort){
        visto[ind]=true;
        ind=pai[ind];
      }
      return;
    }
    tort=pai[tort];
    hare=pai[pai[hare]];
  }
  while(ind!=tort){
    visto[ind]=true;
    ind=pai[ind];
  }
  isciclo[hare]=true;
  visto[hare]=true;
  hare=pai[hare];
  while(hare!=tort){
    isciclo[hare]=true;
    visto[hare]=true;
    hare=pai[hare];
  }

}

int main(){
  freopen("shuffle.in", "r", stdin);
	freopen("shuffle.out", "w", stdout);
  cin.tie(NULL);cin.sync_with_stdio(false);
  int n;cin>>n;
  for (int i=1;i<=n;i++) cin>>pai[i];
  for (int i=1;i<=n;i++) floyd(i);  
  int total=0;
  for (int i=1;i<=n;i++) if (isciclo[i])total++;
  cout<<total<<endl;
}
