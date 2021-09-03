#include<bits/stdc++.h>
using namespace std;
 
#define int long long

/*
    Fast Walsh Hadamard Transform 
    Works just like a FFT but for bitwise operations such as ^ | &
    O(m*2^m)
*/

//outputs some crazy coeficients, use transformed function
template<char op, bool inv = false> vector<int> FWHT(vector<int> f) {
	int n = f.size();
	for (int k = 0; (n-1)>>k; k++) for (int i = 0; i < n; i++) if (i>>k&1) {
		int j = i^(1<<k);
		if (op == '^') f[j] += f[i], f[i] = f[j] - 2*f[i];
		if (op == '|') f[i] += (inv ? -1 : 1) * f[j];
		if (op == '&') f[j] += (inv ? -1 : 1) * f[i];
	}
	if (op == '^' and inv) for (auto& i : f) i /= n;
	return f;
}
 
//Outputs the convolution for given operation
template<char op> vector<int> transformed(vector<int> f){
  f = FWHT<op>(f);
  for(auto &x : f) x *= x;
  f = FWHT<op, true>(f);
  return f;
}
 

 
 
int32_t main(){

 
 
  int n, m, k; cin >> n >> m >> k;
  int nn = n * n; k *= 2;
  
  int MAX = (1 << m);
  int MAGIC = (1 << m) - 1;
 
  vector<int> N(MAX); 
  for(int i = 0; i < n ; ++i){
    string s; cin >> s;
    int x = 0;
    for(int j = 0; j < m; ++j) x += (1 << j) * (s[j] - 'A');
    N[x]++;
  }
 
 
  vector<int> F = transformed<'^'>(N);
 
  vector<int> G(F);

    //SOS DP FOR THE PROBLEM
  for(int i = 0;i < m; ++i) for(int mask = 0; mask < (1<<m); ++mask){
    if(mask & (1<<i))
      G[mask] += G[mask^(1<<i)];
  }
 
 
  for(int i = 0; i < MAX; ++i) G[i] = nn - G[i];
 
  int ans = 0;
  for(int i = 0; i < MAX; ++i){
    ans += (G[i] >= k);
  }
  cout << ans << "\n";
}
