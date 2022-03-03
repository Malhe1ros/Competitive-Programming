#include <bits/stdc++.h>

using namespace std;


struct sparse{
	vector<vector<int>> indo;
	int f(int a,int b){
		return min(a,b);
	}
	sparse(const vector<int>& arr){
		int n=arr.size();
		int k=32-__builtin_clz(n);
		indo.assign(k+1,vector<int>(n));
		indo[0]=arr;
		int t=1;
		for (int i=1;i<k;i++){
			for (int j=0;j<=arr.size()-(1<<i);j++){
				indo[i][j]=f(indo[i-1][j],indo[i-1][j+t]);
			}
			t=(t<<1);
		}
	}
	int query(int a,int b){//[a,b[
		//b++;
		int d=b-a;
		int k=31-__builtin_clz(d);
		return f(indo[k][a],indo[k][b-(1<<k)]);
	}
};

signed main(){
	int n,q;cin>>n>>q;
	vector<int>v(n);
	for(int i=0;i<n;i++){
		cin>>v[i];
		//cout<<v[i]<<endl;
	}	
	sparse st(v);
	while(q--){
		int a,b;cin>>a>>b;
		//cout<<a<<" "<<b<<endl;
		cout<<st.query(a,b)<<'\n';
	}
}
