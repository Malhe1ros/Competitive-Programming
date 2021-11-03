#include <bits/stdc++.h>
 
using namespace std;
 
//Solves https://codeforces.com/gym/103388/problem/N

struct MergeSortTree{
	vector<vector<int>> seg;
	int size;
	MergeSortTree(vector<int>& v){
        int n=1;
        while(n<v.size()) n=n<<1;
        seg.resize(2*n);
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

	//return how many elements are less than or equal to x in range [l,r[
	int LEQ(int l,int r,int x){
		return LEQ(l,r,x,0,0,size);
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


signed main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int n,q;cin>>n>>q;
	vector<int>va(n);
	for(int i=0;i<n;i++)cin>>va[i];
    MergeSortTree mst(va);
	while(q--){
		int a, b, c;cin>>a>>b>>c;
		a--;
		//cout<<a<<" "<<b<<" "<<c<<endl;
		if (va[a]>=b)cout<<0<<'\n';
		else {
			auto ans=mst.LEQ(a+1,min(a+1+c,n),b-1);
			int tot=min(a+1+c,n)-(a+1);
			cout<<tot-ans<<'\n';
		}
	}
}
