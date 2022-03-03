#include <bits/stdc++.h>
 
using namespace std;
 
#define ld long double
#define ll long long
//#define int ll
#define PB push_back
#define MP make_pair
#define FOR(i, j) for(int i=0;i<j;i++)
#define sz(x) (int)x.size()

typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;
typedef vector<VI> VVI;

//USE FOR DEBBUGING STUFF;
/* 
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

signed main(){
	GO FAST
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		VI v(n);
		FOR(i,n)cin>>v[i];
	}
}
*/
