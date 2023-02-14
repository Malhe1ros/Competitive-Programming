#include <bits/stdc++.h>

using namespace std;

/*
    Chicken MCNugget theorem, given the equation 
    a*x + b*y where x>=0 && y>=0

    The biggest number that cannot be formed is a*b-a-b
    The number of non negative integers that cannot be formed is (a-1)*(b-1)/2; (suposing gcd == 1)

    ------------------------------

    For this problem: https://competition.binus.ac.id/inc2020/I.pdf
    x>=1 and y>=1
    So the biggest number that cannot be formed is a*b
    And the number of non negative integers that cannot be formed is (a-1)*(b-1)/2 + a + b
*/

const int maxi = 1000000000000ll;
int calc(int a,int b){
    int g = __gcd(a,b);
    int nposso = ((g-1)*maxi)/g;
    a/=g;
    b/=g;
    return nposso + ((a-1)*(b-1))/2 + a + b;   
}

signed main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n,q;cin>>n>>q;
  vector<int> v(n);
  for(int i = 0;i<n;i++)cin>>v[i];
  map<int,int> mapa;
    for(int i = 0;i<n;i++){
        for(int j = i+1;j<n;j++){
            mapa[calc(v[i],v[j])]++;
        }
    }
    vector<int> caras;
    for(auto k:mapa){
        caras.push_back(k.second);
    }
    bitset<125001> bt;
    bt[0] = 1;
    for(auto k:mapa){
        auto bt1 = bt<<k.second;
        bt|=bt1;
    }
    while(q--){
        int a;cin>>a;
        cout<<(bt[a] ?  "YES" : "NO")<<'\n';
    }
}
