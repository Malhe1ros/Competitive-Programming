#include <bits/stdc++.h>

using namespace std;

vector<int> primos;
vector<int> fato;
void sieve(int n){
  fato.assign(n,-1);
  for (int i=2;i<n;i++){
    if (fato[i]==-1) primos.push_back(i);
    for (int j=0;j<primos.size() && i*primos[j]<n;j++){
      fato[i*primos[j]]=primos[j];
      if (i%primos[j]==0) break;
    }
  }
}
vector<int> fatorar(int n){
    if (n==1) return vector<int>();
    vector<int> ans;
    while(fato[n]!=-1){
        ans.push_back(fato[n]);
        n/=fato[n];
    }
    ans.push_back(n);
    return ans;
    
}
