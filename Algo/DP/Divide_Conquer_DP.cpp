#include <bits/stdc++.h>
 
using namespace std;
//solves https://www.spoj.com/problems/ADAMOLD/
#define int long long 
#define ld long double
#define ll long long
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
 
const int maxn=5010;
int dp[maxn][maxn];//dp[i][j] has the mininimum value of using i buckets and ending at index j;
int custo[maxn][maxn];//custo[i][j] has the cost of subarray from [i to j];
const int INF=1e10;

//function to calculate the cost of trying to get the last bucket on k;
//[dp[i-1][k]] is solving for [0,k] using i-1 buckets;
// custo[k+1][m] is solving for [k+1,m] using 1 bucket;
int costAt(int i,int m,int k){
	if(i>m)return INF;
	return dp[i-1][k]+custo[k+1][m];
}

//this function solve the whole row in N*logN
void solve(int i,int l,int r,int searchL,int searchR){
	if(l>r)return;//base case to leave recursion
	int mid=(l+r)/2;//mid
	int validR=min(mid,searchR);//if we are at point mid, we have to find our answer on at least [0,mid], so we bound the maximum value of the right side by myself;
	if(searchL>validR){//if there is no best place i quit;
		dp[i][mid]=INF;
		return;
	}
	//i know my answer will be on [searchL,searchR] so i supose it will be on searchR and try the rest of the values;
	pii best={costAt(i,mid,validR),validR};
	for(int k=searchL;k<validR;k++){
		best=min(best,MP(costAt(i,mid,k),k));//get the minimum over the valid values;
	}
	dp[i][mid]=best.first;
	solve(i,l,mid-1,searchL,best.second);// i know the answer for the left side will be on [0,mybest];
	solve(i,mid+1,r,best.second,searchR);// i know the answer for the right side will be on [mybest,n-1];
	
}

 int32_t main(){
	 int n,q;cin>>n>>q;
	 vector<int>v(n);
	 FOR(i,n)cin>>v[i];
	 for (int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			custo[i][j]=custo[i][j-1]+(v[j]^v[i]);// now custo[a][b] has a^a + a^(a+1) + a^(a+2) + a^(a+3) + ... + a^(b-1) + a^b;
		} 
	 }
	 for (int i=1;i<n;i++){
		 for(int j=i-1;j>=0;j--){
			 custo[j][i]+=custo[j+1][i];//custo[a][b] has all pairs over a to b;
		 }
	 }
	FOR(i,n) dp[0][i]=custo[0][i];//base case, if we have no buckets and end at i we have custo[0][i]
	for(int i=1;i<=q;i++)solve(i,0,n-1,0,n-1);//solving for all rows (bucket sizes);
	cout<<dp[q][n-1]<<endl;//suposing i use q buckets and end at n-1;
	
 }

