#include <bits/stdc++.h>

using namespace std;
#define double long double
const double eps = 1e-8;
const double inf = 1e18;
#define MP make_pair
#define ltj(X)                                    \
  if (s == -1 || MP(X[j], N[j]) < MP(X[s], N[s])) \
  s = j
struct lp_solver
{
  int m, n;
  vector<int> N, B;
  vector<vector<double>> D;

  lp_solver(const vector<vector<double>> &A, const vector<double> &b, const vector<double> &c) : m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vector<double>(n + 2))
  {
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
        D[i][j] = A[i][j];
    }
    for (int i = 0; i < m; i++)
    {
      B[i] = n + i;
      D[i][n] = -1;
      D[i][n + 1] = b[i];
    }
    for (int j = 0; j < n; j++)
    {
      N[j] = j;
      D[m][j] = -c[j];
    }
    N[n] = -1;
    D[m + 1][n] = 1;
  }
  void pivot(int r, int s)
  {
    double *a = D[r].data(), inv = 1 / a[s];
    for (int i = 0; i < m + 2; i++)
    {
      if (i != r && abs(D[i][s]) > eps)
      {
        double *b = D[i].data(), inv2 = b[s] * inv;
        for (int j = 0; j < n + 2; j++)
          b[j] -= a[j] * inv2;
        b[s] = a[s] * inv2;
      }
    }
    for (int j = 0; j < n + 2; j++)
      if (j != s)
        D[r][j] *= inv;
    for (int i = 0; i < m + 2; i++)
      if (i != r)
        D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  }
  bool simplex(int phase)
  {
    int x = m + phase - 1;
    for (;;)
    {
      int s = -1;
      for (int j = 0; j < n + 1; j++)
      {
        if (N[j] != -phase)
          ltj(D[x]);
      }
      if (D[x][s] >= -eps)
        return true;
      int r = -1;
      for (int i = 0; i < m; i++)
      {
        if (D[i][s] <= eps)
          continue;
        if (r == -1 || MP(D[i][n + 1] / D[i][s], B[i]) < MP(D[r][n + 1] / D[r][s], B[r]))
          r = i;
      }
      if (r == -1)
        return false;
      pivot(r, s);
    }
  }
  double solve()
  {
    int r = 0;
    for (int i = 1; i < m; i++)
    {
      if (D[i][n + 1] < D[r][n + 1])
        r = i;
    }
    if (D[r][n + 1] < -eps)
    {
      pivot(r, n);
      if (!simplex(2) || D[m + 1][n + 1] < -eps)
        return -inf;
      for (int i = 0; i < m; i++)
      {
        if (B[i] == -1)
        {
          int s = 0;
          for (int j = 1; j < n + 1; j++)
            ltj(D[i]);
          pivot(i, s);
        }
      }
    }
    bool ok = simplex(1);
    vector<double> x = vector<double>(n); // os valores escolhidos pra cada x[i] (se quiser eles tbm, so retornar)
    for (int i = 0; i < m; i++)
    {
      if (B[i] < n)
        x[B[i]] = D[i][n + 1];
    }
    return ok ? D[m][n + 1] : inf;
  }
};
// Maximiza c^T x s.t. Ax <= b, x >= 0
//t1 t2... tn <= theta*omega
//-t1 -t2... -tn <= -theta*omega
// 1 1 1 1 .. 1 <= omega
// -1 -1 -1 -1 .. -1 <= -omega
// 1 <= b_i
// -1 <= -a_i;
signed main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n;cin>>n;
  vector<int> v;
  vector<pair<int,int>> lr;
  for(int i = 0;i<n;i++){
    int t,a,b;cin>>t>>a>>b;
    v.push_back(t);
    lr.push_back({a,b});
  }
  int t;cin>>t;

  while(t--){
    double theta,omega;cin>>theta>>omega;

    vector<vector<double>> a;
    vector<double> b;
    vector<double> c;
    for(int i = 0;i < n;i++){
      c.push_back(v[i]);
    }
    
    for(int i = 0;i<3;i++)
      a.push_back(vector<double>(n));
    
    for(int i = 0;i<n;i++){
      a[0][i] = v[i];
      //a[1][i] = -v[i];
      a[1][i] = 1;
      a[2][i] = -1;
    }
    b = {theta*omega+eps,omega+eps,-omega-eps};
    for(int i = 0;i<n;i++){
      a.push_back(vector<double>(n));
      a.back()[i] = 1;
      b.push_back(lr[i].second+eps);
      a.push_back(vector<double>(n));
      a.back()[i] = -1;
      b.push_back(-lr[i].first-eps);
    }
    auto ans = lp_solver(a,b,c);
    //cout<<ans.solve()<<endl;
    auto resp = ans.solve();
   // cout<<resp<<endl;
    if(round(resp)==omega*theta) cout<<"yes\n";
    else cout<<"no\n";
  }
}
