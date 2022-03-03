#include <bits/stdc++.h>

using namespace std;


struct DSU{
    int* arr;
    DSU(int size){
        arr = new int[size];
		for(int i=0;i<size;i++)arr[i]=-1;
    }
    int find(int a){
        int ac=a;
        while(arr[a]>=0){
            a=arr[a];
        }
        while(arr[ac]>=0){
            int cop=arr[ac];
            arr[ac]=a;
            ac=cop;
        }
        return a;
    }
    void unir(int a,int b){
        int paia=find(a);
        int paib=find(b);
        if (paia==paib) return;
		if(arr[paia]>arr[paib])swap(paia,paib);
        arr[paia]+=arr[paib];
		arr[paib]=paia;
    }
};

signed main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int n,q;cin>>n>>q;
	DSU dsu(n);
	while(q--){
		int a,b,c;cin>>a>>b>>c;
		//cout<<b<<" "<<c<<endl;
		if(a){
			cout<<(dsu.find(b)==dsu.find(c))<<'\n';
		}
		else{
			dsu.unir(b,c);
		}
	}
}
