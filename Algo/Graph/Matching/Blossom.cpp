#include <iostream>
#include <vector>
using namespace std;

const int    N = 500000;
int          n;
vector<int>  edges[N];

int lca( vector<int> &match, vector<int> &base, vector<int> &p,
         int a, int b ) 
{
    vector<bool>  used( match.size() );

    while( true )  {
        a = base[a];
        used[a] = true;
        if( match[a] == -1 )   break;
        a = p[match[a]];
    }

    while( true )  {
        b = base[b];
        if( used[b] )   return b;
        b = p[match[b]];
    }
}

void markPath( vector<int> &match, vector<int> &base, vector<bool> &blossom,
               vector<int> &p, int v, int b, int children ) 
{
     for( ; base[v]!=b ; v=p[match[v]] )  {
          blossom[base[v]] = blossom[base[match[v]]] = true;
          p[v] = children;
          children = match[v];
     }
}

int findPath( vector<int> &match, vector<int> &p, int root ) 
{
    vector<bool>  used( n );
    for( int i=0 ; i<p.size() ; ++i )   p[i] = -1;

    vector<int>  base( n );
    for( int i=0 ; i<n ; ++i )   base[i] = i;
    used[root] = true;
    int  qh = 0;  int qt = 0;
    vector<int>  q( n );
    q[qt++] = root;
    while( qh < qt )  {
        int v = q[qh++];
        for( int to : edges[v] )  {
            if( base[v] == base[to]  ||  match[v] == to )
	            continue;
            if( to == root  ||  match[to] != -1  &&
	            p[match[to]] != -1 )  
            {
                int  curbase = lca( match, base, p, v, to );
                vector<bool>  blossom( n );
                markPath( match, base, blossom, p, v, curbase, to );
                markPath( match, base, blossom, p, to, curbase, v );
                for( int i=0 ; i<n ; ++i )
                    if( blossom[base[i]] )  {
                        base[i] = curbase;
                        if( !used[i] )  {
                            used[i] = true;
                            q[qt++] = i;
                        }
                    }
            }
            else if( p[to] == -1 ) 
            {
                p[to] = v;
                if( match[to] == -1 )   return to;
                to = match[to];
                used[to] = true;
                q[qt++] = to;
            }
        }
    }
    return -1;
}

vector< pair<int,int> > maxMatching() 
{
    vector<int>  match( n, -1 ),  p( n );

    for( int i=0 ; i<n ; ++i )  {
        if( match[i] == -1 )  {
            int  v = findPath( match, p, i );
            while( v != -1 )  {
                int  pv  = p[v];
                int  ppv = match[pv];
                match[v] = pv;
                match[pv] = v;
                v = ppv;
            }
        }
    }

    vector< pair<int,int> >  thePath;

    for( int i=0 ; i<n ; ++i )
        if( match[i] != -1 )
            thePath.emplace_back( i, match[i] );

    return thePath;
}

void addEdge(int u,int v){
    edges[u].push_back(v);
    edges[v].push_back(u);
}

signed main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    cin>>n;
    vector<string> v(n);
    vector<int> teste(n);
    vector<int> valor(n);
    for(int i=0;i<n;i++){
        string a;cin>>v[i]>>a>>valor[i];
        if(a[0]=='a')teste[i]=2;
        else if(a[0]=='s')teste[i]=0;
        else teste[i]=1;
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(teste[i]==0){//antes
                if(abs(valor[i]-valor[j])==2){
                    if(teste[j]!=0){
                        addEdge(i,j);
                    }
                }
            }
            else if(teste[i]==1){
                if(abs(valor[i]-valor[j])==2){
                    if(teste[j]!=1){
                        addEdge(i,j);
                    }
                }             
            }
            else{
                if(abs(valor[i]-valor[j])==2){
                    addEdge(i,j);
                }
            }
        }
    }
    auto ans=maxMatching();
    cout<<(ans.size())/2<<endl;
    for(auto k:ans){
        if(k.first<k.second){
            //cout<<k.first<<" "<<k.second<<endl;
            if((teste[k.first]==0) || (teste[k.second]==1)){
                cout<<v[k.first]<<" "<<v[k.second]<<'\n';
            }
            else cout<<v[k.second]<<" "<<v[k.first]<<'\n';
        }
    }
}
