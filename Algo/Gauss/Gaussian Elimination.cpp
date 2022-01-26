#include<bits/stdc++.h>

using namespace std;

/*
  Runs in O(N^3);
  
  Gaussian elimination with partial pivoting;
  how to use:
  matrix[i][j] = coefficient of j in the ith equation;
  matrix[i].back() = independent term of the ith equation;
  
  gaussian(matrix) returns the rank of the matrix;
  matrix[i][i] has the value of the ith variable after the iteration;
*/

const double EPSILON = 1e-10;

typedef double T;
typedef vector<T> VT;
typedef vector<VT> VVT;

int gaussian(VVT &a) {
  int n = a.size();
  int m = a[0].size();
  int r = 0;
  for (int c = 0; c < m && r < n; c++) {
    int j = r;
    for (int i = r + 1; i < n; i++)
      if (fabs(a[i][c]) > fabs(a[j][c])) j = i;
    if (fabs(a[j][c]) < EPSILON) continue;
    swap(a[j], a[r]);

    T s = 1.0 / a[r][c];
    for (int j = 0; j < m; j++) a[r][j] *= s;
    for (int i = 0; i < n; i++) if (i != r) {
      T t = a[i][c];
      for (int j = 0; j < m; j++) a[i][j] -= t * a[r][j];
    }
    r++;
  }
  return r;
}

map<pair<int,int>,pair<int,int>> state0;
map<pair<int,int>,pair<int,int>> state1;
string s1,s2;

int acha(string&s,int ind,char qual){
	for(int i=ind-1;i>=0;i--){
		//cout<<i<<endl;
		if(s[i]==qual){
			int j=i-1;
			int p=ind-1;
			for(;j>=0;j--){
				if(s[j]==s[p]){
					p--;
				}
				else break;
			}
			//cout<<i<<" "<<j<<endl;
			if(j==-1)return i+1;
		}
	}
	return 0;
}

int n;
const pair<int,int> trash={10000,10000};
void solve(int a=0,int b=0){
	if(a==n || b==n){
		state0[{a,b}]=trash;
		state1[{a,b}]=trash;
		return;
	}
	int na=a;
	int nb=b;

	if(state0.find(make_pair(a,b))==state0.end()){
		if(s1[a]=='0')a++;
		else a=acha(s1,a,'0');
		if(s2[b]=='0')b++;
		else b=acha(s2,b,'0');
		state0[{na,nb}]={a,b};
		solve(a,b);
	}
	a=na;
	b=nb;

	if(state1.find(make_pair(a,b))==state1.end()){
		if(s1[a]=='1')a++;
		else a=acha(s1,a,'1');
		if(s2[b]=='1')b++;
		else b=acha(s2,b,'1');
		state1[{na,nb}]={a,b};
		solve(a,b);
	}
}


signed main(){
	cout<<fixed<<setprecision(3);
	
	while(1){
		state0.clear();
		state1.clear();
		cin>>s1>>s2;
		if((s1==s2) && (s1=="0"))return 0;
		n=s1.length();
		
		solve(0,0);
		int id=0;
		map<pair<int,int>,int> conv;
		for(auto k:state0){
			conv[k.first]=id++;
		}
		VVT matriz(id,VT(id+1));
		T meio=0.5;
		for(auto k:state0){
			//cout<<k.first.first<<" "<<k.first.second<<" "<<k.second.first<<" "<<k.second.second<<endl;
			if(k.first.first==n){
				matriz[conv[k.first]][conv[k.first]]=1;
				matriz[conv[k.first]].back()=1;
			}
			else if(k.first.second==n){
				matriz[conv[k.first]][conv[k.first]]=1;
				matriz[conv[k.first]].back()=0;
			}
			else{
				matriz[conv[k.first]][conv[k.first]]+=-1;
				matriz[conv[k.first]][conv[state0[k.first]]]+=meio;
				matriz[conv[k.first]][conv[state1[k.first]]]+=meio;
			}
		}
		
		gaussian(matriz);
		
		cout<<matriz[conv[{0,0}]].back()<<endl;
		//return 0;

	}
}
