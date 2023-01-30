#include <bits/stdc++.h>

using namespace std;
#define int long long

/*
  subset sum in O(N*max)
  return maior S tal que existe uma subset sum menor ou igual a S
*/

int subset_sum(vector<int> w, int t) {
  int a = 0, b = 0;
  while (b < w.size() && a + w[b] <= t) a += w[b++];
  if (b == w.size()) return a;
  int m = *max_element(w.begin(), w.end());
  vector<int> u, v(2*m, -1);
  v[a+m-t] = b;
  for(int i = b; i < w.size(); i++) {
    u = v;
    for(int x = 0; x < m; x++) v[x+w[i]] = max(v[x+w[i]], u[x]);
    for (int x = 2*m; --x > m;) 
      for(int j = max(0ll, u[x]); j < v[x]; j++)
        v[x-w[j]] = max(v[x-w[j]], j);
  }
  for (a = t; v[a+m-t] < 0; a--) ;
  return a;
}


signed main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n,x;cin>>n>>x;
  int maxi = 0;
  vector<int> v;
  for(int i = 0;i<n;i++){
    int a;cin>>a;
    maxi = max(a,maxi);
    if(a<=x) v.push_back(a);
  }
  if(v.empty()){
    cout<<maxi<<'\n';
    return 0;
  }
  if(v.size()<=2){
    cout<<maxi<<'\n';
    return 0;
  }
  if(v.size()<=4){
    cout<<max(x+1,maxi)<<'\n';
    return 0;
  }
  sort(v.rbegin(),v.rend());
  for(int i = 0;i<4;i++){
    if(!v.empty())v.pop_back();
  }

  reverse(v.begin(),v.end());
  int T = 0;
  for(auto k:v)T+=k;
  n = v.size();
  int teste;
  for(int i =0;i<n;i++){
    int q = n;
    q--;
    int tot = T;
    tot-=v[i];
    int cnt = 0;
    for(int j = 0;j<n;j++){
      if(i!=j){
        tot-=v[i];
        cnt++;
      }
      if(cnt==2)break;
    }
    //maxi = max(1 + (q-1)*x + tot - (q-2),maxi);
  }

  int soma = 0;
  for(int i = 0;i<v.size();i++){
    v[i] = x-(v[i]-1);
    soma+=v[i];
  }
  //cout<<soma<<endl;
  int ans = subset_sum(v,(soma+1)/2);
  //cout<<ans<<endl;
  //cout<<ans<<'\n';
  ans = max(ans,soma-ans);
  //cout<<ans<<endl;
  cout<<max(1+x+ans,maxi)<<'\n';

}
