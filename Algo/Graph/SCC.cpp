#include<bits/stdc++.h>
using namespace std;

#define MAXN 100010

/*
Dois vértices i e j estão fortemente conectados em um grafo direcionado G, se
existe caminho direcionado de i para j e de j para i em G.
PE: posicao de entrada  PS: posicao de saida
(v,w) é aresta da árvore ou avanço se e somente se PE(v) < PE(w)
(v,w) é aresta de retorno se e somente se PE(v) > PE(w) e PS(v) < PS(w)
(v,w) é aresta de cruzamento se e somente se PE(v) > PE(w) e PS(v) > PS(w)
low(v) = min{v, PE(z)}, onde z é o vértice de menor profundidade de entrada
localizado no mesmo componente conexo de v, que pode ser alcançado a partir de v,
através de zero ou mais arestas de arvore seguidas por, no máximo, uma aresta de
retorno ou cruzamento.
*/

int idx[MAXN]; // vetor com id de cada vertice (posicao de entrada)
int low[MAXN]; // vetor com lowpt
bool active[MAXN]; // vetor indicando se o no ta na ativo na arvore de recursao
vector<int> v[MAXN]; // lista de adjacencia
vector<int> temp; // vetor temporario para impressao, pilha de recursao


vector<vector<int>> sccs;

void dfs(int x, int _root, int &t){
    low[x] = idx[x] = ++t; // att low e id
    active[x] = true; // att raiz
    temp.push_back(x); // ad na pilha de recur
    // printf(">> %d: %d %d\n", x, low[x], idx[x]);

    for(int i = 0; i < v[x].size(); ++i){
        if(!idx[v[x][i]]){ // se o adj nao foi vis ainda (aresta de arvore)
            dfs(v[x][i], _root, t); // passo recursivo
            low[x] = min(low[x], low[v[x][i]]); // tento atualizar lowpt do atual
        }else{ // eh de avanco, retorno ou cruzamento
            if(active[v[x][i]] && idx[v[x][i]] < idx[x]){
                // primeira condicao: estao na msm arvore
                // segunda condicao: eh aresta de retorno ou cruzamento
                low[x] = min(low[x], idx[v[x][i]]); // tenta atualizar lowpt de x
            }
        }
    }

    // printf("<< %d: %d %d\n", x, low[x], idx[x]);
    if(low[x] == idx[x]){ // x raiz de arvore (eh forte)
        // printf("Componente fortemente conexa: ");
        sccs.push_back({});
        while(true){
            // printf("%d ", temp.back());
            sccs.back().push_back(temp.back());
            active[temp.back()] = false;
            if(temp.back() == x){ // se cheguei na arvore
                temp.pop_back(); break; // tiro raiz e paro de tirar
            }else temp.pop_back(); // vou consumindo a lista
        }
        // printf("\n");
    }
}

int main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int a, b; cin >> a >> b; a--, b--;
        v[a].push_back(b);
    }

    int t = 0;
    for(int i = 0; i < n; ++i){
        if(!idx[i]) dfs(i, i, t); // se nao foi visitado ainda, visite
    }
    vector<int> ans(n);
    for(int i = 0; i < sccs.size(); ++i){
      for(auto x : sccs[i]){
        ans[x] = i + 1;
      }
    }
    cout << sccs.size() << endl;
    for(auto x : ans) cout << x << " " ; cout << endl;
}
