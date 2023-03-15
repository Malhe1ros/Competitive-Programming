#include<bits/stdc++.h>

using namespace std;

#define int long long

/*
    Partisan game: jogado num dag onde existem várias peças, e cada aresta do DAG tem uma cor branca ou preta
    O primeiro jogador só pode mover as peças entre arestas brancas e o segundo jogador só pode mover entre arestas pretas
    Podemos ter várias peças na mesma casa.
    O score de um nó é definido por:
        Seja A o maximo entre todos os nós que eu pego de arestas brancas
        Seja B o minimo entre todos os nós que eu pego de arestas pretas
        A < score < B
        1. score = O menor inteiro em valor absoluto
        2. Se não existir acima, um número da forma x/2^k que minimize k
    
    Se o score for >0 o primeiro ganha
    Se for <=0 o segundo ganha
*/

struct frac{
    int num,den;
    frac(int a,int b){
        num = a;
        den = b;
    }
    frac(){

    }
};

//return true if a<b
bool geq(frac a,frac b){
    return a.num*b.den<a.den*b.num;
}
int chao(frac a){
    if(a.num==0)return 0;
    if(a.num<0){
        if(abs(a.num)%a.den==0)return -abs(a.num)/a.den;
        return -(abs(a.num)/a.den)-1;
    }
    else{
        return a.num/a.den;
    }
}
/*
    Retorna:
        O menor inteiro em modulo entre a & b
        O numero da forma x/2^k com menor k possivel entre a & b
*/
frac between(frac a,frac b){
    {
        int leftBound = chao(a)+1;
        int rightBound = chao(b);
        if(!geq(frac(rightBound,1),b))rightBound--;
        if(leftBound<=rightBound){
            if(leftBound>=0){
                return frac(leftBound,1);
            }
            if(leftBound<0 && rightBound>=0)return frac(0,1);
            return frac(rightBound,1);
        }
    }
    int mult = 1;
    frac cpa = a;
    while(true){
        if(cpa.den!=1)
            cpa.den/=2;
        else cpa.num*=2;
        mult*=2;
        int nxtInt = chao(cpa)+1;
        frac nxtFrac = frac(nxtInt,mult);
        if(geq(a,nxtFrac) && geq(nxtFrac,b))return nxtFrac; 
    }
}

frac getState(vector<int>v);
//black = 1, white = -1, empty = 0;
//first guy moves, can eat black or white up one
frac getWhite(vector<int> v){//quero maximizar
    frac ini = frac(INT_MIN,1);
    for(int i=0;i<v.size();i++){
        if(v[i]==1){
            v[i] = 0;
            auto ans = getState(v);
            if(geq(ini,ans))ini = ans;
            v[i] = 1;
        }
        else if(v[i]==-1){
            if(i>0 && v[i-1]==0){
                v[i-1] = -1;
                v[i] = 0;
                auto ans = getState(v);
                if(geq(ini,ans))ini = ans;
                v[i] = -1;
                v[i-1] = 0;
            }
        }
    }
    return ini;
}

//second guy moves, can eat white or black one up
frac getBlack(vector<int> v){//wants minimize   
    frac ini = frac(INT_MAX,1);
    for(int i=0;i<v.size();i++){
        if(v[i]==-1){
            v[i] = 0;
            auto ans = getState(v);
            if(geq(ans,ini))ini = ans;
            v[i] = -1;
        }
        else if(v[i]==1){
            if(i>0 && v[i-1]==0){
                v[i-1] = 1;
                v[i] = 0;
                auto ans = getState(v);
                if(geq(ans,ini))ini = ans;
                v[i] = 1;
                v[i-1] = 0;
            }
        }
    }
    return ini;
}

map<vector<int>,frac> dp;
frac getState(vector<int> v){
    if(dp.find(v)!=dp.end())return dp[v];
    frac a = getWhite(v);
    frac b = getBlack(v);
    return dp[v] = between(a,b);
}
frac soma(frac a,frac b){
    int na = a.num;
    int da = a.den;


    int nb = b.num;
    int db = b.den;

    int nn = na*db+nb*da;
    int dn = da*db;

    return frac(nn,dn);
}
signed main(){

    int n;cin>>n;
    vector<vector<int>> v(n,vector<int>(n));
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            char c;cin>>c;
            if(c=='.') v[j][i] = 0;
            else if (c=='W')v[j][i] = -1;
            else v[j][i] = 1;
        }
    }

    frac ini(0,1);
    for(auto k:v){
        ini = soma(ini,getState(k));
    }
    if(geq(frac(0,1),ini))cout<<"Takahashi\n";
    else cout<<"Snuke\n";
}
