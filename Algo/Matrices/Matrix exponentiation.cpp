#include <bits/stdc++.h>
 
using namespace std;

#define int  long long
 
int MOD=1e9+7;

void matrix_mult(vector<vector<int>>& a,vector<vector<int>> &b){
    int n=a.size();
    vector<vector<int>> g(n,vector<int>(n));
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            int total=0;
            for (int k=0;k<n;k++){
                total+=(a[i][k]*b[k][j])%MOD;
                total=total%MOD;    
            }
            g[i][j]=total;
 
        }
    }
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) a[i][j]=g[i][j];
    
}
 
vector<vector<int>> solve(vector<vector<int>>&v,int k ){
  vector<vector<int>> ans(v.size(),vector<int>(v.size()));
  for (int i=0;i<v.size();i++)ans[i][i]=1;
    while(k>0){
        if (k%2==1){
            matrix_mult(ans,v);
            k--;
        }
        else{
            matrix_mult(v,v);
            k/=2;
        }
    }
    return ans;
}
