#include <bits/stdc++.h>

//solves https://www.spoj.com/problems/STABLEMP/


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

int main(){
    GO FAST;
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        int pref[n][n];
        FOR(i,n){
            int a;cin>>a;a--;
            FOR(j,n){
            cin>>pref[a][j];
            pref[i][j]--;
        }}
        int mpref[n][n];
        FOR(i,n){
            int b;cin>>b;b--;
            FOR(j,n){
            int a;
            cin>>a;
            a--;
            mpref[b][a]=j;
        }}
        vector<int> match(n,-1);
        vector<int> ids(n,0);
        queue<int> testes;
        FOR(i,n){
            testes.push(i);
        }
        while(!testes.empty()){
            auto o=testes.front();
            testes.pop();
            int mulher=pref[o][ids[o]];

            if (match[mulher]==-1){
                match[mulher]=o;
            }
            else{    
                int outpret=match[mulher];
                if (mpref[mulher][outpret]>mpref[mulher][o]){
                    ids[outpret]++;
                    testes.push(outpret);
                    match[mulher]=o;
                }
                else{
                    ids[o]++;
                    testes.push(o);
                }
            }
        }
        FOR(i,n){
            cout<<i+1<<" "<<match[i]+1<<endl;
        }
    }
}
