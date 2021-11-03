#include <bits/stdc++.h>
 
using namespace std;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<
pair<int,int>,
null_type,
less<pair<int,int>>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

struct UpdatableMergeSortTree{
	vector<ordered_set> seg;
	vector<int> arr;
	int size;
	UpdatableMergeSortTree(vector<int>& v){
        int n=1;
        while(n<v.size()) n=n<<1;
        seg.resize(2*n);
		arr=v;
		size=n;
        build(v,0,0,size);
    
	}

	
	void build(vector<int>&v,int ind,int l,int r){
		for(int i=l;i<r;i++){
			seg[ind].insert({v[i],i});
			
		}
		if (r-l==1)return;
		int mid = l+(r-l)/2;
		build(v,2*ind+1,l,mid);
		build(v,2*ind+2,mid,r);
		
	}

	void update(int ind,int valor,int x,int lx,int rx){
		seg[x].erase({arr[ind],ind});
		seg[x].insert({valor,ind});
		if (rx-lx==1)return;
		int mid = lx+(rx-lx)/2;
		if (ind<mid)update(ind,valor,2*x+1,lx,mid);
		else update(ind,valor,2*x+2,mid,rx);
	}

	void update(int ind,int valor){
		update(ind,valor,0,0,size);
		arr[ind]=valor;
	}

	//return how many elements are less than or equal to x in range [l,r[
		
	int LEQ(int l,int r,int x){
		return LEQ(l,r,x,0,0,size);
	}

	int LEQ(int l,int r,int x,int ind,int lx,int rx){
		if(rx<=l || lx>=r) return 0;
		if (l<=lx && rx<=r){
			
			return seg[ind].order_of_key({x,INT_MAX});
		}
		int mid=lx+(rx-lx)/2;
		return LEQ(l,r,x,2*ind+1,lx,mid) + LEQ(l,r,x,2*ind+2,mid,rx);
	}
};


signed main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	vector<int>va={5,4,39,292,1,1,1,2,39,4,3,2,1};
    UpdatableMergeSortTree mst(va);
	while(1){
		char a;cin>>a;
		if (a=='U'){
			int ind,v;cin>>ind>>v;
			mst.update(ind,v);
		}
		else{
			int a;int b;int c;
			cin>>a>>b>>c;
			
			cout<<mst.LEQ(a,b,c)<<endl;
		}
		
	}
	
}
