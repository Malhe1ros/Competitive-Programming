#include <bits/stdc++.h>

using namespace std;
/*
  Stable marriage
  O(N*M);
  Os vetores estao em ordem de preferencia, ou seja:
  first[i] = ordenado pela pessoa de second que mais quer
  first[i][0] = pessoa de second que i mais prefere
  E vice-versa

  Pode ter relações não monogamicas na direita,  cap[i] representa quantas pessoas o second pode ter;
  Para stable matching marriage, cap[i] = 1 para todo i; 
*/
std::vector<std::vector<int>> stableMarriage(std::vector<std::vector<int>> first, std::vector<std::vector<int>> second, std::vector<int> cap) {
	assert(cap.size() == second.size());
	int n = (int) first.size(), m = (int) second.size();
	// if O(N * M) first in memory, use table
	std::map<std::pair<int, int>, int> prio;
	std::vector<std::set<std::pair<int, int>>> current(m);
	for(int i = 0; i < n; i++) {
		std::reverse(first[i].begin(), first[i].end());
	}
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < (int) second[i].size(); j++) {
			prio[{second[i][j], i}] = j;
		}
	}
	for(int i = 0; i < n; i++) {
		int on = i;
		while(!first[on].empty()) {
			int to = first[on].back();
			first[on].pop_back();
			if(cap[to]) {
				cap[to]--;
				assert(prio.count({on, to}));
				current[to].insert({prio[{on, to}], on});
				break;
			}
			assert(!current[to].empty());
			auto it = current[to].end();
			it--;
			if(it->first > prio[{on, to}]) {
				int nxt = it->second;
				current[to].erase(it);
				current[to].insert({prio[{on, to}], on});
				on = nxt;
			}
		}
	}
	std::vector<std::vector<int>> ans(m);
	for(int i = 0; i < m; i++) {
		for(auto it : current[i]) {
			ans[i].push_back(it.second);
		}
	}
	return ans;
}



const int maxn = 1010;
pii qualbrinquedo[maxn];
int quemta[maxn];
int qtd[maxn][maxn];
VI quemjogouminimo[maxn];
int pref[maxn][maxn];
int id[maxn];
signed main(){
    GO FAST;
    int n,m;cin>>n>>m;
    if(m<n){
      cout<<"impossible\n";
      return 0;
    }
    int d,q;cin>>d>>q;
    auto tira = [&](int tempo,int cria){
      if(cria==0)return;
      int brinq = qualbrinquedo[cria].second;
      int ti = qualbrinquedo[cria].first;
      qualbrinquedo[cria] = {0,0};
      quemta[brinq] = 0;
      qtd[cria][brinq]+=tempo-ti;
    };
    auto bota = [&](int tempo,int cria,int brinq){
      qualbrinquedo[cria] = MP(tempo,brinq);
      quemta[brinq] = cria;
      if(pref[cria][brinq]==0){
        id[cria]++;
        pref[cria][brinq] = id[cria];
        
      }
    };
    FOR(i,q){
      int s,crianca,brinq;
      cin>>s>>crianca>>brinq;
      
      if(brinq==-1){
        tira(s,crianca);
      }
      else{
        tira(s,quemta[brinq]);
        tira(s,crianca);
        bota(s,crianca,brinq);
      }
    }
    FOR(i,n)tira(d,i+1);
    VVI left;
    VVI right;
    for(int i = 1;i<=n;i++){
      vector<pair<int,int>> caras;
      for(int j = 1;j<=m;j++){
        if(pref[i][j]==0){
          caras.push_back(MP(INT_MAX,j));
        }
        else caras.push_back(MP(pref[i][j],j));
      }
      sort(all(caras));
      VI a;
      FOR(K,sz(caras))a.push_back(caras[K].second-1);
      left.push_back(a);
    }
    for(int j = 1;j<=m;j++){
      VPII caras;
      for(int i = 1;i<=n;i++){
        caras.PB(MP(qtd[i][j],i));
      }
      sort(all(caras));
      VI b;
      FOR(K,sz(caras))b.push_back(caras[K].second-1);
      right.push_back(b);
    }

    vector<int> t(n,1);

    auto ans = stableMarriage(right,left,t);

    for(auto k:ans)cout<<k[0]+1<<" ";
    cout<<'\n';
    
    
    
}
