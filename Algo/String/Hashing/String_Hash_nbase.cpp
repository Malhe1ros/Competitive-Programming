#include <bits/stdc++.h>
 
using namespace std;


const int mod1=1e9+9;//big prime number
const int mod2=1e9+7;
const int mod3=90003047; 
const int qntdbase=3;
const int bases[qntdbase]={mod1,mod2,mod3};


const int base=10;
const int maxn=1e6+10;
int expBase[maxn][qntdbase];

void precalc(){
    for(int j=0;j<qntdbase;j++){
    expBase[0][j]=1;
    for (int i=1;i<maxn;i++){
        expBase[i][j]=(expBase[i-1][j]*base)%bases[j];
    }
    }
}

struct StringHash{
    vector<vector<int>> hsh;
    //REMEMBER TO RUN PRECALC
    StringHash(){

    }
    StringHash(string& _s){
        hsh=vector<vector<int>>(_s.length()+1,vector<int>(qntdbase,0));
        for (int j=0;j<qntdbase;j++){
          for (int i=0;i<_s.length();i++){
              hsh[i+1][j]=((hsh[i][j]*base)%bases[j] + (_s[i]-'0'))%bases[j];
          }
        }
    }

    //interval =  [a,b] closed
    vector<int> get_value(int a,int b){
        vector<int> ans(qntdbase);
        for (int j=0;j<qntdbase;j++){
          ans[j]=(bases[j] + hsh[b+1][j] - ((hsh[a][j])*expBase[b-a+1][j])%bases[j])%bases[j];
        }
        return ans;
    }
    
};


signed main(){
  
}
