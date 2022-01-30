#include<bits/stdc++.h>

using namespace std;

/*
    Given polynomial f and points ps, returns the f(p) for all points in ps;
*/

const int mod=998244353;
const int pr=3;

int mod_pow(long long a,long long b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return res;
}
inline void ntt(vector<int> &a,bool flag){
	int n=a.size();
	vector<int> &x=a,y(n);
	if(n==1) return;
	
	long long s=flag?(mod-1)/n:(mod-1-(mod-1)/n), z=mod_pow(pr,s);
	
	vector<int> zt(n/2+1,1);
	for(int i=1;i<=n/2;i++) zt[i]=zt[i-1]*z%mod;
	for(int k=1,h=n/2;k<n;k<<=1,h>>=1){
		int ki=0;
		for(int i=0;i<h;i++){
			long long coef=zt[k*i];
			for(int j=0;j<k;j++){
				int t0=x[j+ki],t1=x[j+ki+n/2];
				y[j+2*ki]=(t0+t1)%mod;
				y[j+2*ki+k]=(t0-t1+mod)*coef%mod;
			}
			ki+=k;
		}
		x.swap(y);
	}
	if(!flag){
		long long in=mod_pow(n,mod-2);
		for(int i=0;i<n;i++) x[i]=x[i]*in%mod;
	}
}
vector<int> convolution(vector<int> a,vector<int> b){
	int n=a.size()+b.size()-1;
	if(n<=40){
		vector<int> res(n);
		for(int i=0;i<a.size();i++){
			for(int j=0;j<b.size();j++){
				res[i+j]+=1LL*a[i]*b[j]%mod;
				if(res[i+j]>=mod) res[i+j]-=mod;
			}
		}
		return res;
	}
	int m=1;
	while(m<n) m*=2;
	a.resize(m);
	b.resize(m);
	ntt(a,true),ntt(b,true);
	for(int i=0;i<a.size();i++) a[i]=1LL*a[i]*b[i]%mod;
	ntt(a,false);
	a.resize(n);
	return a;
}
vector<int> inverse(vector<int> &f,int m){
	int c=1;
	while(c<m) c*=2;
	m=c;
	vector<int> a0(1,(int)mod_pow(f[0],mod-2));
	for(int d=2;d<=m;d*=2){
		vector<int> f0(d);
		//a1=2a0-f*a0*a0 mod x^d
		for(int i=0;i<d;i++){
			if(i>=f.size()) break;
			f0[i]=f[i];
		}
		a0.resize(d);
		vector<int> a2=a0;
		ntt(a2,true);
		ntt(f0,true);
		for(int i=0;i<d;i++) f0[i]=1LL*a2[i]*f0[i]%mod;
		ntt(f0,false);
		for(int i=0;i<d/2;i++) f0[i]=0;
		ntt(f0,true);
		for(int i=0;i<d;i++) f0[i]=1LL*f0[i]*a2[i]%mod;
		ntt(f0,false);
		for(int i=d/2;i<d;i++){
			a0[i]=(a0[i]+mod-f0[i]);
			if(a0[i]>=mod) a0[i]-=mod;
		}
		//5fft(d)
	}
	return a0;
}
inline pair<vector<int>,vector<int>> polynomial_division(vector<int> f,vector<int> g){
	//divide f(x)=f[0]+f[1]x+f[2]x^2+... by g(x)=g[0]+g[1]x+...
	vector<int> rf=f,rg=g;
	int n=f.size(),m=g.size();
	if(n<m){
		return make_pair(vector<int>(1,0),f);
	}
	if((n+m)<=30){
		int ig=1;
		if(g.back()!=1) ig=mod_pow(g.back(),mod-2);
		vector<int> p(n-m+1);
		for(int i=n-1;i>=(m-1);i--){
			int s=1LL*ig*f[i]%mod;
			p[i-m+1]=s;
			for(int j=m-1;j>=0;j--){
				f[i+j-m+1]=(f[i+j-m+1]+mod-1LL*g[j]*s%mod);
				if(f[i+j-m+1]>=mod) f[i+j-m+1]-=mod;
			}
		}
		return make_pair(p,f);
	}
	reverse(rf.begin(),rf.end());
	reverse(rg.begin(),rg.end());
	rg.resize(n-m+1);
	rg=inverse(rg,n-m+1);
	rg.resize(n-m+1);
	rf.resize(n-m+1);
	vector<int> p=convolution(rf,rg);
	p.resize(n-m+1);
	reverse(p.begin(),p.end());
	vector<int> q=convolution(p,g);
	for(int i=0;i<q.size();i++){
		q[i]=(f[i]+mod-q[i])%mod;
	}
	int qsize=q.size();
	for(int i=qsize-1;i>0;i--){
		if(q[i]) break;
		qsize--;
	}
	q.resize(qsize);
	return make_pair(p,q);
}
vector<int> multipoint_evaluation(vector<int> &f,vector<int> ps){
	int m=ps.size(),c=1,bit=0;
	while(c<m){
		c*=2;
		bit++;
	}
	if(c==1){
		vector<int> g={mod-ps[0],1};
		auto p0=polynomial_division(f,g);
		return p0.second;
	}
	ps.resize(c);
	vector<vector<vector<int>>> ta(bit);
	for(int i=0;i<bit;i++) ta[i].resize(1<<(bit-i));
	for(int i=0;i<c;i++) ta[0][i]={mod-ps[i],1};
	for(int i=1;i<bit;i++){
		for(int j=0;j<ta[i-1].size()/2;j++){
			ta[i][j]=convolution(ta[i-1][2*j],ta[i-1][2*j+1]);
		}
	}
	vector<int> res(c);
	vector<vector<int>> cur={f};
	for(int i=0;i<bit;i++){
		if(cur[0].size()<80){
			for(int j=0;j<m;j++){
				int k=(long long)j*cur.size()/c;
				long long coef=1;
				for(int s=0;s<cur[0].size();s++){
					res[j]=(res[j]+coef*cur[k][s]%mod);
					if(res[j]>=mod) res[j]-=mod;
					coef=coef*ps[j]%mod;
				}
			}
			res.resize(m);
			return res;
		}
		vector<vector<int>> nex(cur.size()*2);
		for(int j=0;j<cur.size();j++){
			nex[2*j]=polynomial_division(cur[j],ta[bit-1-i][2*j]).second;
			nex[2*j+1]=polynomial_division(cur[j],ta[bit-1-i][2*j+1]).second;
		}
		cur.swap(nex);
	}
	for(int i=0;i<cur.size();i++){
		res[i]=polynomial_division(cur[i],ta[0][i]).second[0];
	}
	res.resize(m);
	return res;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n,m;
	cin >> n >> m;
	vector<int> a(n),b(m);
	for(int i=0;i<n;i++) cin >> a[i];
	for(int i=0;i<m;i++) cin >> b[i];
	
	vector<int> c=multipoint_evaluation(a,b);
	
	for(int i=0;i<m;i++) cout << c[i] <<" \n"[i+1==m];
	return 0;
}
