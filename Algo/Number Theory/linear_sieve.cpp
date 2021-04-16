#include<bits/stdc++.h>
using namespace std;

vector<int> primos;
vector<bool> is_composite;
void sieve(int n){
  is_composite.resize(n);
  for (int i=2;i<n;i++){
    if (!is_composite[i]) primos.push_back(i);
    for (int j=0;j<primos.size() && i*primos[j]<n;j++){
      is_composite[i*primos[j]]=true;
      if (i%primos[j]==0) break;
    }
  }
}
