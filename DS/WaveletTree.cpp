#include <bits/stdc++.h>
 
using namespace std;
 
//tested with https://judge.yosupo.jp/problem/range_kth_smallest and https://codeforces.com/gym/103388/problem/N
struct node{
	vector<int> ps;
	int l,r;
	node(){
		l=-1;
		r=-1;
	}
};


struct WaveletTree{
    vector<node> seg;
    int size;
	int mini,maxi;
	vector<int>v;
	WaveletTree(vector<int>&v1){
		v=v1;
		mini=*min_element(v.begin(),v.end());
		maxi=*max_element(v.begin(),v.end());
		maxi++;
		vector<int> ind(v1.size());
		for(int i=0;i<v1.size();i++){
			ind[i]=i;
		}
        seg.push_back(node());
		build(ind,0,mini,maxi);
		
	}
	void build(vector<int>&indices,int x,int lx,int rx){
		if (rx-lx==1){
			return;
		}
		int mid=(lx+rx)/2;
		vector<int> left;
		vector<int> right;
        seg[x].ps.push_back(0);
		for(int i=0;i<indices.size();i++){
			if (v[indices[i]]<mid){
				seg[x].ps.push_back(seg[x].ps.back()+1);
				left.push_back(indices[i]);
			}
			else{
				seg[x].ps.push_back(seg[x].ps.back());
				right.push_back(indices[i]);
			}
		}
		if(!left.empty()){
			seg[x].l=seg.size();
			seg.push_back(node());
			build(left,seg.size()-1,lx,mid);
		}
		if(!right.empty()){
			seg[x].r=seg.size();
			seg.push_back(node());
			build(right,seg.size()-1,mid,rx);
		}
	}

    int LEQ(int ind,int lo,int hi,int r,int x){
		
		if (ind==-1)return 0;
		if (r==0)return 0;
		
		int mid=(lo+hi)/2;
		
		if (lo>x)return 0;

		if (hi<=(x+1)) return r;
		
		return LEQ(seg[ind].l,lo,mid,seg[ind].ps[r],x)+LEQ(seg[ind].r,mid,hi,r-seg[ind].ps[r],x);
	}

	//RETURNS HOW MANY ELEMENTS FROM L TO R ARE LESS THAN OR EQUAL TO X
	//[l,r[
	int LEQ(int l,int r,int x){
		l++;
		return LEQ(0,mini,maxi,r,x)-LEQ(0,mini,maxi,l-1,x);
	}

	//RETURNS HOW MANY ELEMENTS FROM L TO R ARE EQUAL TO X
	//[l,r[
	int countEqual(int l,int r,int x){
		return LEQ(l,r,x)-LEQ(l,r,x-1);
	}

	int kth(int l,int r,int k,int ind,int lo,int hi){
		if(hi-lo==1)return lo;
		
		int rb=seg[ind].ps[r];;
		int lb=seg[ind].ps[l-1];;
		
		int totleft=rb-lb;
		int mid = (lo+hi)/2;

		if (k<totleft) return kth(lb+1,rb,k,seg[ind].l,lo,mid);
		else return kth(l-lb,r-rb,k-totleft,seg[ind].r,mid,hi);
	}

	//RETURNS THE KTH LARGEST ELEMENT FROM L TO R;
	//[l,r[
	// k \in [0,r-l[
	int kth(int l,int r,int k){
		l++;
		return kth(l,r,k,0,mini,maxi);
	}



};


signed main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int n,q;cin>>n>>q;
	vector<int> v(n);
	for(int i=0;i<n;i++) cin>>v[i];
	WaveletTree wt(v);
	while(q--){
		int a,b,c;
		cin>>a>>b>>c;
		cout<<wt.kth(a,b,c)<<'\n';
	}
}
