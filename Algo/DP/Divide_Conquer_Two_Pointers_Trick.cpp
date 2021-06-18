#include <bits/stdc++.h>

//solves https://codeforces.com/contest/868/problem/F

using namespace std;
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
int n,k;
const int maxn=1e5+10;
int occ[maxn];
const int maxk=21;
int dp[maxk][maxn];
int v[maxn];
int tot=0;
void add(int ind){
	tot+=occ[v[ind]]++;
}
void rm(int ind){
	occ[v[ind]]--;
	tot-=occ[v[ind]];
}
int pl=0;
int pr=-1;
const int INF=1e12;
 
int C(int a,int b){
  while(pl<a){
    rm(pl++);
  }
  while(pl>a){
    add(--pl);
  }
  while(pr>b){
    rm(pr--);
  }
  while(pr<b){
    add(++pr);
  }
  return tot;
}
 
void solve(int i,int l,int r,int searchL,int searchR){
	if(l>r)return;
	int mid = (l+r)/2;
	pii melhor={INF,-1};
  int validR=min(searchR,mid);
  for (int j=searchL;j<=validR;j++){
		
    melhor=min(melhor,MP(dp[i-1][j]+C(j+1,mid),j));
	}
	if(melhor.second==-1){
		dp[i][mid]=INF;
		return;
	}
	dp[i][mid]=melhor.first;
	solve(i,l,mid-1,searchL,melhor.second);
	solve(i,mid+1,r,melhor.second,searchR);
}
 
signed main(){
	GO FAST
	cin>>n>>k;
	FOR(i,n)cin>>v[i];
 
	FOR(i,n){
		add(i);
		dp[0][i]=tot;
 
	}
	FOR(i,n) rm(i);
	
	for(int i=1;i<k;i++){
		solve(i,0,n-1,0,n-1);
	}
	/*FOR(i,n){
		FOR(j,k){
			cout<<dp[i][j]<<" ";
		}
		cout<<endl;
	}*/
	cout<<dp[k-1][n-1]<<'\n';
}
