#include <bits/stdc++.h>


using namespace std;
#define int long long

long long floor_sum(long long n,long long a,long long b,long long m){
	if(!a) return (b/m)*(n+1);

	if(a>=m || b>=m){
		return (a/m)*n*(n+1)/2 + (n+1)*(b/m) + floor_sum(n,a%m,b%m,m);
	}

	long long z = (a*n+b)/m-1;

	if(z<0) return 0;
	
	return (z+1)*n - floor_sum(z,m,m-b-1,a);
}

// sum (alfa + step*x)//n for x in [l,r];
int floor_sum(int alfa,int step,int n,int l,int r){
	if(l>r)return 0;
	int l_sum = floor_sum(l-1,step,alfa,n);
	int r_sum = floor_sum(r,step,alfa,n);
	return r_sum-l_sum;
}

const int MOD = 998244353;
signed main(){
	cin.tie(NULL)->sync_with_stdio(false);

	int n;cin>>n;
	vector<int> v(n);
	for(int i =0;i<n;i++)cin>>v[i];

	sort(v.begin(),v.end());
	int ans = v[0]+1;
	
	int tenho = v[0]*n;

	map<int,int> mapa;
	for(auto k:v)mapa[k]++;

	bool gamb = 1;
	int step = n;
	for(auto [x,y] : mapa){
		
		if(gamb){
			step-=y;
			gamb=0;continue;
		}
		int ant = prev(mapa.find(x))->first;

		int rang = x-ant;

		
		ans+=floor_sum(tenho,step,n,1,rang)+rang;
		
		ans%=MOD;

		tenho+=rang*step;
		
		//tenho%=MOD;

		step-=y;
	}
	ans+=MOD;
	ans%=MOD;
	cout<<ans<<'\n';
}


