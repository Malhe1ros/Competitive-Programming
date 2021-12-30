#include <bits/stdc++.h>
 
using namespace std;
//#define int long long

struct Fraction{
    int num,den;

    Fraction(int a=0,int b=1){
        int todiv=__gcd(abs(a),abs(b));
        num=a/todiv;
        den=b/todiv;
    }
    Fraction operator+(const Fraction& other) const{
        int newden=(den*other.den)/__gcd(den,other.den);
        int newnum=num*(newden/den)+other.num*(newden/other.den);
        return Fraction(newnum,newden);
    }
    Fraction operator*(const Fraction&other) const{
        return Fraction(other.num*num,den*other.den);
    }
    Fraction operator-(const Fraction& other) const{
        return Fraction(num,den)+Fraction(-other.num,other.den);
    }
    Fraction operator/(const Fraction&other){
        return Fraction(num,den)*Fraction(other.den,other.num);
    }
    bool operator==(const Fraction&other) const{
        return (num==other.num) && (den==other.den);
    }
    bool operator!=(const Fraction&other)const {
        return !(Fraction(num,den)==other);
    }
    void print(){
        cout<<num<<" / "<<den<<endl;
    }
};


int n;
int testa(vector<Fraction>&v,int b,int e){
    Fraction dif(v[e].num-v[b].num,e-b);
    int tot=0;
    auto beg=v[b];
    for(int i=b;i<n;i++){

        if(beg!=v[i]){

            //cout<<endl;
            tot++;       
        }
        beg=beg+dif;
    }
    beg=v[b]-dif;
    for(int i=b-1;i>=0;i--){
        if(beg!=v[i]){

            tot++;
        }
        beg=beg-dif;
    }
    return tot;
}
signed main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t;cin>>t;
    while(t--){
        cin>>n;
        vector<Fraction>v(n);
        for(int i=0;i<n;i++){
            int a;cin>>a;
            v[i]=Fraction(a);
        }
        int maior=n-1;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                maior=min(maior,testa(v,i,j));
            }
        }
        cout<<maior<<'\n';
    }
}
