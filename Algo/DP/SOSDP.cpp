#include <bits/stdc++.h>
 
using namespace std;
 
#define ld long double
#define ll long long
//#define int ll
#define FF first.first
#define FS first.second
#define SF second.first
#define SS second.second
#define PB push_back
#define MP make_pair
#define all(cont) cont.begin(),cont.end()
#define rall(cont) cont.rbegin(), cont.rend()
#define FOR(i, j) for(int i=0;i<j;i++)
#define GO cin.tie(NULL);
#define FAST ios_base::sync_with_stdio(false);
#define AE cout<<"AEEEE"<<endl;
#define _L cout<<"Linha "<<__LINE__<<endl;
#define sz(x) (int)x.size()

typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;
typedef vector<VI> VVI;

const long double PI = 3.14159265359;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll a, ll b){return uniform_int_distribution<ll>(a, b)(rng);}

#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}

void print(vector<int>v){
	cout<<"[";
	FOR(i,sz(v)){
		cout<<v[i];
		if(i+1!=sz(v))cout<<", ";
	}
	cout<<"]"<<endl;
}

void print(pii p){
	cout<<"{"<<p.first<<", "<<p.second<<"}"<<endl;
}

template<typename Container>
void print(Container beg){
    cout<<"[";
    for(auto k:beg){
        cout<<k<<" ";
    }
    cout<<"]"<<endl;
}

const int N=22;
const int invertor=(1<<N)-1;
int inv(int x){
   // deb(x,invertor);
    return x^invertor;
}

const int maxn=(1<<N);
int A[maxn];
/*
int dp[maxn][N+1];
void SOS(){
    for(int mask = 0; mask < (1<<N); ++mask){
	    dp[mask][0] = A[mask];	//handle base case separately (leaf states)
        for(int i = 1;i <= N; ++i){
            int bit=(1<<(i-1));
            if(mask & bit)
                dp[mask][i] = min(dp[mask][i-1] , dp[mask^bit][i-1]);
            else
                dp[mask][i] = dp[mask][i-1];
        }
    }
}*/

int F[maxn];
void SOS(){
    for(int i = 0; i<(1<<N); ++i)
        F[i] = A[i];
    for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
        if(mask & (1<<i))
            F[mask] =min(F[mask], F[mask^(1<<i)]);
    }
}

signed main(){
   GO FAST
   int n;cin>>n;

   VI v(n);
   FOR(i,maxn)A[i]=INT_MAX;
   FOR(i,n){
       int a;cin>>a;
       v[i]=a;
       A[a]=a;
   }
   SOS();
   FOR(i,n){
       auto R=F[inv(v[i])];
       if(R==INT_MAX)cout<<-1<<' ';
       else cout<<R<<' ';
   }
   cout<<'\n';
    
}
