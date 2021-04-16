#include <bits/stdc++.h>
using namespace std;
#define ll long long

//solves https://www.spoj.com/problems/INVDIV/

ll power(ll a,ll b){
	ll ans=1;
	while(b>0){
		if (b & 1){
			ans*=a;
			b--;
			//ans=ans%MOD;
		}
		a=a*a;
		//a=a%MOD;
		b=b>>1;		
	}
	return ans;
}
 
const int MAXN=1e8+10;
int v[MAXN];
int sdiv[MAXN];
int expv[MAXN];
int gamb[MAXN];
vector<int> primos;
const int maiorzao=1e8;
void sieve(){
	for (int i=0;i<MAXN;i++){
		v[i]=-1;
		sdiv[i]=-1;
		expv[i]=1;
		gamb[i]=-1;
	}
	//memset(v,-1,MAXN);
	//memset(mfunc,maiorzao,MAXN);
	//memset(expv,1,MAXN);
	for (int i=2;i<MAXN;i++){
		if (v[i]==-1) primos.push_back(i);
		for (int j=0;j<primos.size() && i*primos[j]<MAXN;j++){
			v[i*primos[j]]=primos[j];
			if (i%primos[j]==0) {
				expv[i*primos[j]]=expv[i]+1;
				break;
			}
			else expv[i*primos[j]]=1;
		}
	}
			sdiv[1]=1;
	for (int i=2;i<MAXN-1;i++){
		if (v[i]==-1)sdiv[i]=i+1;
		else{
			int p=i/v[i];
			if (p%v[i]!=0){
				sdiv[i]=(v[i]+1)*sdiv[p];
			}
			else{
				sdiv[i]=(sdiv[p]*(power(v[i],expv[i]+1)-1)/(power(v[i],expv[p]+1)-1));
			}
		}
	}
	for (int i=1;i<MAXN;i++){
		if (sdiv[i]>MAXN)continue;
		if (gamb[sdiv[i]]!=-1)continue;
		gamb[sdiv[i]]=i;
	}
 
 
	
 
}
int32_t main(){
	int t;
	scanf("%d",&t);
	sieve();
	
	while(t--){
		int a;scanf("%d",&a);
		printf("%d\n",gamb[a]);
	}
 
}
