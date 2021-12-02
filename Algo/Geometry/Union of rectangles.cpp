#include <bits/stdc++.h>
 
using namespace std;
/*  
  Calculates the area of union of N rectangles in O(N*logN) 
  uses sweep line, coordinate compression and lazy propagation on segment tree
*/
 
#define ld long double
#define ll long long
#define int ll
#define FF first.first
#define FS first.second
#define SF second.first
#define SS second.second
#define PB push_back
#define MP make_pair
#define all(cont) cont.begin(),cont.end()
#define rall(cont) cont.rbegin(), cont.rend()
#define FOR(i, j) for(int i=0;i<j;i++)
#define RFOR(i, j) for (int i=j;i>=0;i--)
#define GO cin.tie(NULL);
#define FAST ios_base::sync_with_stdio(false);
#define prec(x) cout << fixed << setprecision(x)
#define sz(x) (int)x.size()

typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;
typedef vector<VI> VVI;
typedef priority_queue<int> max_heap;
typedef priority_queue<pii> max_heapii;
typedef priority_queue<int,VI,greater<int>> min_heap;
typedef priority_queue<pii,VPII,greater<pii>> min_heapii;

const long double PI = 3.14159265359;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll a, ll b){return uniform_int_distribution<ll>(a, b)(rng);}

#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}

void print(vector<int>v){
	cout<<"[";
	FOR(i,v.size()){
		cout<<v[i];
		if(i+1!=v.size())cout<<", ";
	}
	cout<<"]"<<endl;
}

void print(pii p){
	cout<<"{"<<p.first<<", "<<p.second<<"}"<<endl;
}
 


struct nd{
	int mini,soma;
	nd(int a,int c){
    mini=a;//the minimum on range
    soma=c;//the sum of lenghts of the minimums
	}
	nd(){
	}
};
//const int neut=2e16;
 

//copied segment tree
template <class nd>
struct segtree{
  nd* arr;//real information
  int* lazy;//lazy information
  int size;//size of my segtree
  nd neutro;//neutral element of op operation
  int lneutro;//neutral element of lazy operation
 
  /*
    apply operation on a and b
    watch out, it is copying a and b everytime, sometimes you need to optimize;
  */
  nd op(nd a,nd b){//updates the minimum and the length of minimums
    //whoever is smaller continues
    if (a.mini>b.mini)return b;
    if (b.mini>a.mini)return a;
    nd novo(a.mini,a.soma+b.soma);//if equal i have sum of lengths
    return novo;
  }
 
  /*
    push lazy from node[inda] to node[indb];
  */
  void pushlazy(int inda,int indb){
    lazy[indb]+=lazy[inda];
  }
 
 
  /*
    apply lazy operation located at ind;
  */
  void applylazyatnode(int ind,int nodesize){
    arr[ind].mini+=lazy[ind];
  }


  segtree(vector<nd>&v,nd neut,int lazyneut=0){
    neutro=neut;
    lneutro=lazyneut;
    int n=v.size();
    size=1;
    while(size<n){
      size*=2;
    }
    arr = new nd[2*size];
    lazy = new int[2*size];
    for (int i=0;i<2*size;i++){
      lazy[i]=lneutro;
      arr[i]=neutro;
    }
    build(v,0,0,size);
  }
  
  void build(vector<nd>&v,int x,int l,int r){
    if (r-l==1){
      if (l<v.size()){
        arr[x]=v[l];
      }
      return;
    }
    int mid = l + (r-l)/2;
    build(v,2*x+1,l,mid);
    build(v,2*x+2,mid,r);
    arr[x]=op(arr[2*x+1],arr[2*x+2]);
  }
  
  void propagate(int x,int l,int r){
    applylazyatnode(x,r-l);
    if(r-l==1){      
      lazy[x]=lneutro;
      return;
    }
    pushlazy(x,2*x+1);
    pushlazy(x,2*x+2);
    lazy[x]=lneutro;
  }
 
  void update(int v,int l,int r,int x,int lx,int rx){
    propagate(x,lx,rx);
    if (lx>=r || rx<=l)return;
    if (lx>=l && rx<=r){
      lazy[x]+=v;
      propagate(x,lx,rx);
      return;
    }
    int mid = lx + (rx-lx)/2;
    update(v,l,r,2*x+1,lx,mid);
    update(v,l,r,2*x+2,mid,rx);
    arr[x]=op(arr[2*x+1],arr[2*x+2]);
  }
 
  void update(int l,int r,int v){
    return update(v,l,r,0,0,size);
  }
 
  nd query(int l,int r,int x,int lx,int rx){
    propagate(x,lx,rx);
    if (lx>=r || rx<=l)return neutro;
    if (lx>=l && rx<=r){
      return arr[x];
    }
    int mid = lx + (rx-lx)/2;
    return op(query(l,r,2*x+1,lx,mid),query(l,r,2*x+2,mid,rx));
  }
 
  nd query(int l,int r){
    return query(l,r,0,0,size);
  }
 
};

signed main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n;cin>>n;
  vector<pair<pair<int,int>,pair<int,int>>> sweep;
  vector<int> comp;
  for(int i=0;i<n;i++){
    int a,b,c,d;cin>>a>>b>>c>>d;
    sweep.push_back({{a,0},{b,d}});//rectangle starting at a is begginning ranging from b to d;
    sweep.push_back({{c,1},{b,d}});//rectangle starting at c is ending ranging from b to d;
    comp.push_back(b);//to coordinate compress;
    comp.push_back(d);
  }

  //coordinate compression
  sort(all(comp));
  comp.resize(unique(comp.begin(), comp.end()) - comp.begin());
  map<int,int> mapa;
  int CONT=0;
  for(auto k:comp){
    mapa[k]=CONT++;
  }
  int todos=comp.back()-comp[0];

  vector<nd>v;
  for(int i=1;i<comp.size();i++){
    v.push_back(nd(0,comp[i]-comp[i-1]));//now every node in the segment tree will have a weight corresponding to the length of the segment
  }

  segtree<nd> seg(v,nd(INT_MAX,0));//neutral element doesn't matter

  sort(all(sweep));//sweep line
  int tot=0;
  int cont=0;
  for(int i=0;i<sz(sweep);i++){
    if (i>0 && sweep[i].FF!=sweep[i-1].FF){
        auto teste=seg.query(0,sz(v));
        //queries how many elements are equal to zero and multiplies by how much time it was happening;
        if (teste.mini==0)tot+=(todos-teste.soma)*(sweep[i].FF - sweep[i-1].FF);
        else tot+=todos*(sweep[i].FF - sweep[i-1].FF);
    }
    auto k=sweep[i];
    if (k.FS==0){
        seg.update(mapa[k.SF],mapa[k.SS],1);//adds a segment
    }
    else seg.update(mapa[k.SF],mapa[k.SS],-1);//removes a segment;
  }

  
  cout<<tot<<'\n';
  
  
}
