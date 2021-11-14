#include <bits/stdc++.h>
 
using namespace std;
/*
Black box to calculate mobius function
*/

const int MAXN=1e6+10;
int min_prime_fact[MAXN];
int mobius[MAXN];
int expv[MAXN];
vector<int> primos;
void sieve(){
	for (int i=0;i<MAXN;i++){
		min_prime_fact[i]=-1;
		mobius[i]=-1;
	}

	for (int i=2;i<MAXN;i++){
		if (min_prime_fact[i]==-1) primos.push_back(i);
		for (int j=0;j<primos.size() && i*primos[j]<MAXN;j++){
			min_prime_fact[i*primos[j]]=primos[j];
			if (i%primos[j]==0) {
				break;
			}
		}
	}
	mobius[1]=1;
	for (int i=2;i<MAXN-1;i++){
    if (min_prime_fact[i]==-1){//primo
      mobius[i]=-1;
    }
		else{
			int p=i/min_prime_fact[i];
			if (p%min_prime_fact[i]==0){//tem p^2
				mobius[i]=0;
			}
			else{
				mobius[i]=mobius[p]*mobius[min_prime_fact[i]];
			}
		}
	}
 
}


signed main(){
  sieve();
}
