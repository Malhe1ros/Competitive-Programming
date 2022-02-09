#include<bits/stdc++.h>

using namespace std;
typedef long long ll;


#define N 510
const int mod=998244353;
int inv[N][N];

ll qp(ll a,int p){
	ll ans=1;
	for(;p;p>>=1,a=a*a%mod)if(p&1)ans=ans*a%mod;
	return ans;
}

int calc_inv_matrix(vector<vector<int>>& a){
	int n=a.size();n--;
	int i,j,k;
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)inv[i][j]=(i==j);
	for(i=1;i<=n;i++){
		if(!a[i][i]){
			int flag=0;
			for(j=i+1;j<=n;j++)
				if(a[j][i]){
					for(k=1;k<=n;k++)swap(a[j][k],a[i][k]);
					swap(inv[j],inv[i]);
					flag=1;
					break;
				}
			if(!flag)return 0;
		}
		ll coe=qp(a[i][i],mod-2);
		for(j=1;j<=n;j++)
			inv[i][j]=inv[i][j]*coe%mod,
			a[i][j]=a[i][j]*coe%mod;
		for(j=1;j<=n;j++){
			if(i==j)continue;
			coe=a[j][i];
			for(k=1;k<=n;k++){
				inv[j][k]=(inv[j][k]-1LL*inv[i][k]*coe)%mod,
				a[j][k]=(a[j][k]-1LL*a[i][k]*coe)%mod;
			}
		}
	}
	return 1;
}
int main(){
	int n;
	int i,j;
	scanf("%d",&n);
	vector<vector<int>>a(n+1,vector<int>(n+1));
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf("%d",&a[i][j]);
	if(!calc_inv_matrix(a))printf("-1");
	else{
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++)printf("%d ",(inv[i][j]+mod)%mod);
			puts("");
		}
	}
	return 0;
}
