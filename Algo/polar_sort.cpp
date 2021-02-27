#include <bits/stdc++.h>
using namespace std;

#define usando double
#define pii pair<usando,usando>
#define x first
#define y second
/*
    Dado n pontos, fazer o polar sort counterclockwise em relação a um deles
    primeiro em relação ao angulo depois em relação a distancia
    (1,0),(0,1),(0,0),(-1,0),(2,0),(0,-1) em relação  a (0,0) -> (0,0),(1,0),(2,0),(0,1),(-1,0),(0,-1)
*/
pii ponto_fixo;
//cross product do vetor A->B com A->C
//B_aXC_a
//cross product positivo se C estiver a esquerda de B
usando cross_product(pii&a,pii&b,pii&c){
    usando xc=c.x-a.x;
    usando yc=c.y-a.y;
    usando xb=b.x-a.x;
    usando yb=b.y-a.y;
    return xc*yb-xb*yc;
}
bool cmp(pii& a,pii& b){
    if (a.y>=ponto_fixo.y && b.y<ponto_fixo.y) return true;
    if (a.y<ponto_fixo.y && b.y>=ponto_fixo.y) return false;
    usando cp=cross_product(ponto_fixo,a,b);
    if (cp==0){
        return ((a.x-ponto_fixo.x)*(a.x-ponto_fixo.x)+(a.y-ponto_fixo.y)*(a.y-ponto_fixo.y))<((b.x-ponto_fixo.x)*(b.x-ponto_fixo.x)+(b.y-ponto_fixo.y)*(b.y-ponto_fixo.y));
    }
    return cp<0;
}
// ordena os pontos em relacao ao pontos[index] em counterclocwise order;
void polar_sort(vector<pii>& pontos,int index){
    ponto_fixo=pontos[index];
    swap(pontos[0],pontos[index]);
    sort(++pontos.begin(),pontos.end(),cmp);
}

