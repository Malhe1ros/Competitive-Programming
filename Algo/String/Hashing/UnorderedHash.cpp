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


int power(int a,int b){
    int ans=1;
    while(b>0){
        if (b&1){
            b--;
            ans*=a;
            ans%=MOD;
        }
        a*=a;
        a%=MOD;
        b/=2;
    }
    return ans;
}

int invMod(int a){
    return power(a,MOD-2);
}

struct UnorderedHash{
    vector<int> hsh;
    //REMEMBER TO RUN PRECALC
    UnorderedHash(string& _s){
        hsh=vector<int>(_s.length()+1,1);
        for (int i=0;i<_s.length();i++){
            hsh[i+1]=(hsh[i]*(_s[i]+base))%MOD;
        }
    }

    //interval =  [a,b] closed
    int get_value(int a,int b){
        return (hsh[b+1] *invMod(hsh[a]))%MOD;
    }

    
};



signed main(){
    precalc();
}
