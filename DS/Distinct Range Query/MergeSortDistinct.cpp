#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int)x.size()

const int INF = INT_MAX;
struct DistinctRangeQuery{
	vector<vector<int>> seg;
	int size;
	DistinctRangeQuery(vector<int>& v){
        int n=1;
        while(n<v.size()) n=n<<1;
        seg.resize(2*n);
        map<int,int> lastOc;
        for(int i=sz(v)-1;i>=0;i--){
          if(lastOc.find(v[i])==lastOc.end()){
            lastOc[v[i]] = i;
            v[i]=INF;
          }
          else{
            int antes = v[i];
            v[i] = lastOc[antes];
            lastOc[antes]=i;
          }
        }
        
		    size=n;
        build(v,0,0,size);
    
	}

	void build(vector<int>&v,int ind,int l,int r){
		if(r-l==1){
			if (l<v.size())seg[ind].push_back(v[l]);
			return;
		}
		int mid = l+(r-l)/2;
		build(v,2*ind+1,l,mid);
		build(v,2*ind+2,mid,r);
		merge(seg[2*ind+1].begin(),seg[2*ind+1].end(),seg[2*ind+2].begin(),seg[2*ind+2].end(),back_inserter(seg[ind]));
	}

	//return how many elements are distinct in [l,r[
	int distinct(int l,int r){
		return (r-l) - LEQ(l,r,r-1,0,0,size);
	}

	int LEQ(int l,int r,int x,int ind,int lx,int rx){
		if(rx<=l || lx>=r) return 0;
		if (l<=lx && rx<=r){
			return upper_bound(seg[ind].begin(),seg[ind].end(),x)-seg[ind].begin();
		}
		int mid=lx+(rx-lx)/2;
		return LEQ(l,r,x,2*ind+1,lx,mid) + LEQ(l,r,x,2*ind+2,mid,rx);
	}
};
int n;

int findNext(DistinctRangeQuery& drq,int beg,int maxi){
  int l = beg+1;
  int r = n+1;
  int melhor = beg+1;
  while(l<r){
    int mid = (l+r)/2;
    if(drq.distinct(beg,mid)<=maxi){
       melhor=mid;
       l=mid+1;
    }
    else{
      r=mid;
    }
  }
  return melhor;
}

int solve(DistinctRangeQuery& drq,int maxi){
  int l=0;
  int tot=0;
  while(l<n){
    l = findNext(drq,l,maxi);
    tot++;
  }
  return tot;
}

signed main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  cin>>n;
  vector<int> v(n);
  for(int i=0;i<n;i++)cin>>v[i];
  DistinctRangeQuery drq(v);
  
  
  
  for(int i=1;i<=n;i++){
    cout<<solve(drq,i)<<' ';
  }
  cout<<'\n';
}
