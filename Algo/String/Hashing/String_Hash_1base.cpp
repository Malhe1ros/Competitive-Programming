#include<bits/stdc++.h>

using namespace std;

#define int long long

const int MOD=1e9+9;//big prime number
const int base=153;//random number larger than the size of the alphabet

const int maxn=1e5+10;
int expBase[maxn];

void precalc(){
    expBase[0]=1;
    for (int i=1;i<maxn;i++){
        expBase[i]=(expBase[i-1]*base)%MOD;
    }
}

struct StringHash{
    vector<int> hsh;
    //REMEMBER TO RUN PRECALC
    StringHash(string& _s){
        hsh=vector<int>(_s.length()+1,0);
        for (int i=0;i<_s.length();i++){
            hsh[i+1]=((hsh[i]*base)%MOD + _s[i])%MOD;
        }
    }

    //interval =  [a,b] closed
    int get_value(int a,int b){
        return (MOD + hsh[b+1] - (hsh[a]*expBase[b-a+1])%MOD)%MOD;
    }

    
};



signed main(){
    precalc();
    string s="aaa";
    StringHash shs(s);

}
