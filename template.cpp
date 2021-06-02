#include <bits/stdc++.h>

// COMPILE WITH g++ d.cpp -w -o d    
using namespace std;

#define ld long double
#define ll long long
#define FF first.first
#define FS first.second
#define SF second.first
#define SS second.second
#define PB push_back
#define MK make_pair
#define all(cont) cont.begin(),cont.end()
#define rall(cont) cont.rbegin(), cont.rend()
#define FOR(i, j, k, in) for(int i=j;i<k;i+=in)
#define RFOR(i, j, k, int) for (int i=j;i>=k;i-=in)
#define REP(i, j) for (int i=0;i<j;i++)
#define RREP(i, j) for (int i=j;i>=0;i--)


typedef pair<int,int> PII;

//DEBBUGGING STUFF, JUST USE deb(a,b,c) and it will print the variables;
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}

int main(){
   
}
