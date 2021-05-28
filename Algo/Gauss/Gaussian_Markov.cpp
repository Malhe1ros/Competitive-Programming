#include <bits/stdc++.h>
    
using namespace std;
 
#define ld long double

//solves https://www.spoj.com/problems/GS/
/*
	This algorithm solves problems involving cyclic expectation, you can solve using markov chains in O(C*V^3), iterating all over a high C constant and aproximating the expected value
	But you can also solve it in O(V^3) converting it into a system of equations and solving with gaussian elimination;
	The trick is explained down below
*/

const int maxn=(int)20;
ld a[maxn][maxn];
//black box to gaussian eliminate (i don't know if it is a valid sentence but looks cool lol);
//in mx we have the matrix + in the last column the value of answer
vector<ld> gauss(const vector< vector<ld> > mx)
{	
	int n=(int)mx.size();
 
	for(int i=0;i<n;i++)
	{	
		memset(a[i],0,sizeof(a[i]));
 
		for(int j=0;j<n+1;j++)
		{
			a[i][j]=mx[i][j];
		}
	}
 
	for(int i=0;i<n;i++)
	{	
		int pos=i;
 
		for(int j=i+1;j<n;j++)
		{
			if(fabs(a[j][i])>fabs(a[pos][i]))
			{
				pos=j;
			}
		}
 
		for(int j=0;j<n+1;j++)
		{
			ld temp=a[i][j];a[i][j]=a[pos][j];
 
			a[pos][j]=temp;
		}
 
		ld now=a[i][i];
 
		for(int j=0;j<n+1;j++)
		{
			a[i][j]/=now;
		}
 
		for(int j=0;j<n;j++)
		{
			if(j!=i)
			{
				ld now=a[j][i];
 
				for(int k=0;k<n+1;k++)
				{
					a[j][k]-=(a[i][k]*now);
				}
			}
		}	
	}
 
	vector<ld> ret;
 
	for(int i=0;i<n;i++)
	{	
		ret.push_back(a[i][n]);
	}
 
	return ret;
}
 


int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    cout<<fixed<<setprecision(5);
    int tt;cin>>tt;
    while(tt--){
        int n,s,t;cin>>n>>s>>t;
        s--;t--;
        vector<vector<ld>> prob(n,vector<ld>(n));
        vector<ld> soma(n);
        for (int i=0;i<n-1;i++){
            int a,b,c;cin>>a>>b>>c;
            a--;b--;
            prob[a][b]=c;
            prob[b][a]=c;
            soma[a]+=c;
            soma[b]+=c;
        }
        if (s==t){
            ld ans=0.0;
            cout<<ans<<'\n';
            continue;
        }
        
        /*
            E(i) = expected value to go from i to T
            ______
            E(i) = 1 + sum{ P[i][j]*E[j] } : The expected value to go from i to T is (1 plus the sum of (the probability of me going to j) times (the expected value to reach T from j));
            E(i) - sum{ P[i][j]*E[j] } = 1;  
            We can write this as (-P[i][0]*E[0]) + (-P[i][1]*E[1]) ... ((1-P[i][i])* E[i]) ... = 1;
                                                                        This different value is because E[i]*P[i][i] is inside the sum

            Imagine writing it for all values of i, in a matrix times a vector, that would be (I-P)*E = 1
            we know that (I-P)E = 1;
            where:
            I = identity matrix;
            P = Probability matrix;
            E = expect value vector;
            1 = vector full of 1's;

            NOTE:
            WE WANT T TO BE A SINK, SO FOR ALL P[T][I]=0 and P[T][T]=1(will be canceled when I-P), AND ALSO E[T]=0; 
            WE WILL HAVE A FULL ROW OF ZEROS AND E[T]=0 SO WE CAN JUST FORGET T FROM THE EQUATION AND WORK WITH A (N-1)*(N-1) MATRIX;

        */
       
        //Creating the identity matrix;
        vector<vector<ld>> id(n,vector<ld>(n,0));
        for (int i=0;i<n;i++) id[i][i]=1;

        //DOING I-P AND TAKING OUT T;
        vector<vector<ld>> finalform;

        for (int i=0;i<n;i++){
            vector<ld> v;
            if (i!=t){
            for (int j=0;j<n;j++){
                if (j!=t)
                v.push_back(id[i][j]-prob[i][j]/soma[i]);
            }
            v.push_back(1);
            finalform.push_back(v);
            }
            
        }
       
       // printv(finalform);
        vector<ld> ans(n,1); 
        //doing this because we took the t out of the equation, so now every value above t has an index-1;
        if(s>t)s--;
        cout<<gauss(finalform)[s]<<'\n';
    }
}
