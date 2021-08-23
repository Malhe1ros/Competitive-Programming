#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MOD=1e9+9;//big prime number
const int mod=1e9+7;
const int base=153;//random number larger than the size of the alphabet

const int maxn=1e6+10;
int expBase[maxn];
int expBase2[maxn];

void precalc(){
    expBase[0]=1;
    expBase2[0]=1;
    for (int i=1;i<maxn;i++){
        expBase[i]=(expBase[i-1]*base)%MOD;
        expBase2[i]=(expBase2[i-1]*base)%mod;
    }
}

struct StringHash{
    vector<pair<int,int>> hsh;
    //REMEMBER TO RUN PRECALC
    StringHash(string& _s){
        hsh=vector<pair<int,int>>(_s.length()+1,{0,0});
        for (int i=0;i<_s.length();i++){
            hsh[i+1].first=((hsh[i].first*base)%MOD + _s[i])%MOD;
            hsh[i+1].second=((hsh[i].second*base)%mod + _s[i])%mod;
        }
    }

    //interval =  [a,b] closed
    pair<int,int> get_value(int a,int b){
        auto p1= (MOD + hsh[b+1].first - ((hsh[a].first)*expBase[b-a+1])%MOD)%MOD;
        auto p2= (mod + hsh[b+1].second - ((hsh[a].second)*expBase2[b-a+1])%mod)%mod;
        return {p1,p2};
    }
    
};

signed main(){
  precalc();
  int t;cin>>t;
  while(t--){
    int maxi=1;
    string s;cin>>s;
    auto hash=StringHash(s);
    int l=0;
    int r=s.length()-1;
    int l1=l;
    int r1=r;
    while(l1<r1){
      if (hash.get_value(l,l1)==hash.get_value(r1,r)){
        l=l1+1;
        r=r1-1;
        maxi+=2;
      }
      l1++;
      r1--;
    }
    if (l>r)maxi--;
    cout<<maxi<<'\n';
  }
}
