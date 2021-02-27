#include <bits/stdc++.h>
using namespace std;

#define usando double
#define pii pair<usando,usando>
#define x first
#define y second
//cross product do vetor A->B com A->C
//B_aXC_a
//cross product positivo se C estiver a esquerda de B
usando cross_product(pii&a,pii&b,pii&c){
    usando xc=c.x-a.x;
    usando yc=c.y-a.y;
    usando xb=b.x-a.x;
    usando yb=b.y-a.y;
    return xc*yb-xb*yc;
}



vector<pii> convex_hull(vector<pii> pontos){
    sort(pontos.begin(),pontos.end());
    vector<pii> ans;
    ans.push_back(pontos[0]);
        //for (auto k:pontos) cout<<"("<<k.first<<" "<<k.second<<") , ";
        //cout<<endl;
    for (int i=1;i<pontos.size();i++){
        //for (auto k:ans) cout<<"("<<k.first<<" "<<k.second<<") , ";
        //cout<<endl;
        if (ans.size()==1 || cross_product(ans[ans.size()-2],ans.back(),pontos[i])<0){
            if(pontos[i]!=ans.back())ans.push_back(pontos[i]);
        }
        else{
            while(ans.size()>=2 && cross_product(ans[ans.size()-2],ans.back(),pontos[i])>=0){
                ans.pop_back();
            }
            if(pontos[i]!=ans.back())ans.push_back(pontos[i]);
        }
    }
        //for (auto k:ans) cout<<"("<<k.first<<" "<<k.second<<") , ";
        //cout<<endl;
    vector<pii> helper;
    helper.push_back(pontos[0]);
        for (int i=1;i<pontos.size();i++){
        //for (auto k:ans) cout<<"("<<k.first<<" "<<k.second<<") , ";
        //cout<<endl;
        if (helper.size()==1 || cross_product(helper[helper.size()-2],helper.back(),pontos[i])>0){
            if(pontos[i]!=helper.back())helper.push_back(pontos[i]);
        }
        else{
            while(helper.size()>=2 && cross_product(helper[helper.size()-2],helper.back(),pontos[i])<=0){
                helper.pop_back();
            }
            if(pontos[i]!=helper.back())helper.push_back(pontos[i]);
        }
    }
    int n=helper.size();
    for (int i=n-2;i>=1;i--){
        ans.push_back(helper[i]);
    }
    return ans;
}
int main(){
    while(1){
    int t;
    cin>>t;
    if (t==0) break;
    vector<pii> pontos;
    while(t--){
        int a,b;cin>>a>>b;
        pontos.push_back({a,b});
    }
    
    vector<pii> ans = convex_hull(pontos);
    cout<<ans.size()<<endl;
    for (auto k:ans)cout<<k.first<<" "<<k.second<<endl;
    //cout<<endl;
    }
}