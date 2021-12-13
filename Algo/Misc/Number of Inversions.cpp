#include <bits/stdc++.h>
 
using namespace std;

#define ll long long

/*
  finds the number of inversions in O(N*logN) using the ideia of merge sort algorithm
  number of inversions = 
  number of inversions on the left side
  number of inversions on the right side
  number of inversions between sides;
  solves https://codeforces.com/contest/1591/problem/D
*/

ll merge_sort(vector<int>& v, vector<int>& aux, int l, int r) {
    if (r <= l) return 0LL;
    int m = l + (r - l) / 2;
    ll res = merge_sort(v, aux, l, m) + merge_sort(v, aux, m + 1, r);
    int x = l, y = m + 1, z = l;
    while (x <= m && y <= r) {
        aux[z++] = v[x] <= v[y] ? v[x++] : (res += m - x + 1, v[y++]);
    }
    while (x <= m) aux[z++] = v[x++];
    while (y <= r) aux[z++] = v[y++];
    while (l <= r) v[--z] = aux[r--];
    return res;
}
ll inversions(vector<int> v) {
    static vector<int> aux;
    int as=aux.size();
    int av=v.size();
    aux.resize(max(as,av));
    return merge_sort(v, aux, 0, av-1);
}
 
signed main(){
	
	int t;cin>>t;
	while(t--){
    int n,maxi;cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    auto tot=inversions(v);
    sort(v.begin(),v.end());
    //deb(tot);
    for(int i=0;i<n;i++){
      if (i>0 && v[i]==v[i-1])tot=0;
    }
    if (tot%2==0)cout<<"YES\n";
    else cout<<"NO\n";
  }
}
