#include <bits/stdc++.h>
 
using namespace std;
 
#define ld long double
#define ll long long
#define int ll
#define FF first.first
#define FS first.second
#define SF second.first
#define SS second.second
#define PB push_back
#define MP make_pair
#define all(cont) cont.begin(),cont.end()
#define rall(cont) cont.rbegin(), cont.rend()
#define FOR(i, j) for(int i=0;i<j;i++)
#define RFOR(i, j) for (int i=j;i>=0;i--)
#define GO cin.tie(NULL);
#define FAST ios_base::sync_with_stdio(false);
typedef pair<int,int> pii;
 
 
 
// Your function
//DEBBUGGING STUFF, JUST USE deb(a,b,c) and it will print the variables;
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}
 
const int maxn = 1010;

ll dp[maxn][maxn];
int best_k[maxn][maxn];

//solves https://www.spoj.com/problems/BRKSTRNG/

/*
    Knuth optimization on dynamic programming;
    Can be used on DPs of the form dp[i][j]=min{ dp[i][k] + dp[k][j] }
    And where best_k[i][j-1]<=best_k[i][j]<=best_k[i+1][j]
    With this property (and other one but no one cares) you can optimize from O(N^3) to O(N^2)
    By knowing your best_k[i][j] is between best_k[i][j-1] and best_k[i+1][j];
*/

ll calc_dp(vector<int>& points) {
  int n = points.size()-2;
  for(int s = 0; s <= n + 1; ++s) {
    for(int l = 0; l + s <= n + 1; ++l) {
      int r = l + s;
      if(s < 2) {
        dp[l][r] = 0;
        best_k[l][r] = l;
        continue;
      }
      dp[l][r] = 1ll << 60;
      for(int k = best_k[l][r - 1]; k <= best_k[l + 1][r]; ++k) {
        ll cur = dp[l][k] + dp[k][r] + (points[r] - points[l]);
        if(dp[l][r] > cur) {
          dp[l][r] = cur;
          best_k[l][r] = k;
        }
      }
    }
  }
  return dp[0][n + 1];
}

int32_t main(){
    int n,k;
    while(cin>>n>>k){
        vector<int>v(k+2);
        v[0]=0;
        FOR(i,k)cin>>v[i+1];
        v[k+1]=n;
        
        cout<<calc_dp(v)<<'\n';
    }

}
