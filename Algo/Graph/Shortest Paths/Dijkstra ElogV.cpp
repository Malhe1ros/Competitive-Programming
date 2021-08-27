#include<bits/stdc++.h>
using namespace std;
 
#define int long long
const int INF=1e18;
struct dijkstra{
	int n;
	vector<vector<pair<int,int>>> grafo;
	dijkstra(int _n){
		n=_n;
		grafo=vector<vector<pair<int,int>>>(n);
	}
	
	void addEdge(int a,int b,int c){
		grafo[a].push_back({b,c});
	}

	//calculates value of shortest path from a to b;
	int min_path(int a,int b){
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap;
		vector<int>dp(n,INF);
		dp[a]=0;
		heap.push({0,a});
		while(!heap.empty()){
			auto olhando=heap.top();
			heap.pop();
			if (olhando.second==b)break;
			if (olhando.second!=a && dp[olhando.second]<olhando.first) continue;
			for (auto k:grafo[olhando.second]){
				if (dp[k.first]>dp[olhando.second]+k.second){
					dp[k.first]=dp[olhando.second]+k.second;
					heap.push({dp[k.first],k.first});
				}
			}
		}
		return dp[b];
	}

	//calculates all values of shortest path from a to all nodes;
	vector<int> min_path(int a){
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap;
		vector<int>dp(n,INF);
		dp[a]=0;
		heap.push({0,a});
		while(!heap.empty()){
			auto olhando=heap.top();
			heap.pop();
			if (olhando.second!=a && dp[olhando.second]<olhando.first) continue;
			for (auto k:grafo[olhando.second]){
				if (dp[k.first]>dp[olhando.second]+k.second){
					dp[k.first]=dp[olhando.second]+k.second;
					heap.push({dp[k.first],k.first});
				}
			}
		}
		return dp;
	}

	//returns the shortest path from a to b;
	vector<int> path(int a,int b){
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap;
		vector<int>dp(n,INF);
		vector<int> ultimo(n,-1);
		dp[a]=0;
		heap.push({0,a});
		while(!heap.empty()){
			auto olhando=heap.top();
			heap.pop();
			if (olhando.second==b)break;
			if (olhando.second!=a && dp[olhando.second]<olhando.first) continue;
			for (auto k:grafo[olhando.second]){
				if (dp[k.first]>dp[olhando.second]+k.second){
					dp[k.first]=dp[olhando.second]+k.second;
					ultimo[k.first]=olhando.second;
					heap.push({dp[k.first],k.first});
				}
			}
		}
		int beg=b;
		vector<int> ans;
		while(beg!=-1){
			ans.push_back(beg);
			beg=ultimo[beg];
		}
		reverse(ans.begin(),ans.end());
		return ans;
	}
};

signed main(){
	int n,m;cin>>n>>m;
	dijkstra dji(n);
	while(m--){
		int a,b,c;cin>>a>>b>>c;
		a--;b--;
		dji.addEdge(a,b,c);
		dji.addEdge(b,a,c);
	}
	auto ans=dji.path(0,n-1);
	if (ans.size()==1){
		cout<<-1<<'\n';
		return 0;
	}
	for (auto k:ans){
		cout<<k+1<<" ";
	}
	cout<<'\n';
}
