#include <bits/stdc++.h>
#include <ext/random>

using namespace std;
 
#define ld long double
#define ll long long
#define int ll
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
__gnu_cxx::sfmt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll a, ll b){return uniform_int_distribution<ll>(a, b)(rng);}
 
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}
 
template<typename Container>
void print(Container beg){
    cout<<"[";
    for(auto k:beg){
        cout<<k<<" ";
    }
    cout<<"]"<<endl;
}
 
void print(vector<int>v){
	cout<<"[";
	FOR(i,sz(v)){
		cout<<v[i];
		if(i+1!=sz(v))cout<<", ";
	}
	cout<<"]"<<endl;
}

/*
  Solves https://atcoder.jp/contests/abc310/tasks/abc310_g

  This problem consists of, given a cactus, every node of the cactus has a number of balls in it

  An operation consists of taking all the balls from your node and passing to the next node

  We want to calculate, for each node, the sum of all final balls in it by doing the operation 1,2,3,...,k times where k<=10^18

  We can use the idea of binary exponentiation to solve the problem, 

  We want to do a HLD like query where where for each node we sum its value of balls in all the next k parents (might have cycle, then sum multiple times over the same node)

  Let's say K=4

  balls[0] = X

  0 points to 1, 1 points to 2, 2 points to 3....

  we want to add X in all nodes [0,3]

  we do:
  {
    balls[1] += X
    0 points to 2
    1 points to 3
  }

  {
    balls[2] += X;
    balls[3] += balls[1]; //that has X
    0 points to 4
    1 points to 5
    2 points to 6
    3 points to 7
  }

  it is like a propagation on a segtree or some binary lifting stuff you might get the idea afterwards.
*/


const int MOD= 998244353;

ll power(ll x, ll y) {
    ll ans = 1;
    x %= MOD;
    while (y > 0) {
        if (y%2==1) ans = (ans*x)%MOD;
        y /= 2;
        x = (x*x)%MOD;
    }
    return ans;
}

ll invMod(ll a){
  return power(a,MOD-2);
}

signed main(){
  GO FAST
  int n,k;cin>>n>>k;
  
  VI a(n);
  FOR(i,n){
    cin>>a[i];
    a[i]--;
  }
  
  VI ball(n);
  FOR(i,n)cin>>ball[i];

  VI ans(n);

  auto apply = [&](){//propagate the values of its children to itself
    VI novobal(n);
    FOR(i,n){
      novobal[a[i]] = (novobal[a[i]] + ball[i])%MOD;
    }
    return novobal;
  };

  auto jmp = [&](){//binary lifting like jumping (one time)
    VI b(n);
    FOR(i,n)
      b[i]=a[a[i]];
    a=b;
  };

  auto soma= [&](VI& alfa,VI x){
    FOR(i,n)alfa[i] = (alfa[i]+x[i])%MOD;
  };

  ball = apply();//we don't consider the initial state in this problem

  int K = k;

  while(k){//normal binary exponentiation

    if(k&1){
      soma(ans,ball);
      
      ball = apply();
    }
    
    soma(ball,apply());
    
    jmp();
    
    k/=2;
  }

  k = K;

  for(auto x:ans){
    cout<<(x*invMod(k))%MOD<<' ';//expected value blabla only in the specific problem
  }
  cout<<'\n';

}
