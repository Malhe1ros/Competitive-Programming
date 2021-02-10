    #include <bits/stdc++.h>
    
    using namespace std;
    
    
    class sparse{
        public:
        vector<vector<int>> indo;
        sparse(vector<int>& arr){
            int k=32-__builtin_clz(arr.size());
            indo.reserve(k+1);
            for (int i=0;i<k;i++){
                indo.push_back(vector<int>(arr.size()));
            }
            for (int i=0;i<arr.size();i++){
                indo[0][i]=arr[i];   
            }
            int t=1;
            for (int i=1;i<k;i++){
                
                for (int j=0;j<=arr.size()-(1<<i);j++){
                    indo[i][j]=min(indo[i-1][j],indo[i-1][j+t]);
                }
                t=(t<<1);
            }
        }
        int query(int a,int b){
            b++;
            int d=b-a;
            int k=31-__builtin_clz(d);
            return min(indo[k][a],indo[k][b-(1<<k)]);
        }
    };

