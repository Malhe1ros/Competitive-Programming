#include <bits/stdc++.h>
 
using namespace std;

const int INF=1e9;

void print(pair<int,int> p){
	cout<<"{"<<p.first<<", "<<p.second<<"}"<<endl;
}

void print(set<pair<int,int>> ss){
  for (auto k:ss){
    print(k);
  }
}

/*
  colorUpdate data structure
  you can add a range [l,r] (it goes by merging every range that any number from [l,r] is inside);
  you can remove a range [l,r] (removes all numbers from [l,r] from all ranges);
  you can query which range is the number u inside;
*/

struct colorUpdate{
  set<pair<int,int>> ranges;
  void add(int l,int r){

    if (ranges.empty()){
      ranges.insert({l,r});
      return;
    }
    
    auto it=ranges.lower_bound({l,-INF});
    int beg=l;
    int fim=r;

    vector<pair<int,int>>toerase;
    if (it!=ranges.begin()) {
      auto previt=prev(it);
      if(previt->second >=l){
        beg=min(previt->first,l);
        fim=max(previt->second,r);
        toerase.push_back(*previt);
      }
    }

    while(it!=ranges.end() && it->first <=r){
      toerase.push_back(*it);
      fim=max(r,it->second);
      it++;
    }

    for(auto k:toerase){
      ranges.erase(k);
    }

    ranges.insert({beg,fim});
  }

  void remove(int l,int r){
    auto it=ranges.lower_bound({l,-INF});
    vector<pair<int,int>> toerase;
    vector<pair<int,int>> toinsert;
    if (it!=ranges.begin()){
      auto previt=prev(it);
      if ((previt->first <= l) && (r <= previt->second)){
        
        if (l!=previt->first)ranges.insert({previt->first,l-1});
        if (r!=previt->second) ranges.insert({r+1,previt->second});
        ranges.erase(previt);
        return;
      }
      if (previt->second >= l){
        toinsert.push_back({previt->first,l-1});
        toerase.push_back(*previt);
      }
    }
    int last=-INF;
    while(it!=ranges.end() && it->first <=r){
      toerase.push_back(*it);
      last=it->second;
      it++;
    }
    if(last!=-INF){
      if((r+1) <= last)toinsert.push_back({r+1,last});
    }
    for(auto k:toerase){
      ranges.erase(k);
    }
    for(auto k:toinsert){
      ranges.insert(k);
    }

  }

  pair<int,int> query(int u){
    auto it=ranges.lower_bound({u,-INF});
    if (it!=ranges.end() && it->first == u){
      return *it;
    }
    if (it==ranges.begin())return {-1,-1};
    it--;
    if (it->first<= u && u <= it->second)return *it;
    return {-1,-1};
  }
};

/*
  CODE FOR TESTING;
*/

const int maxn=1000;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int a, int b){return uniform_int_distribution<int>(a, b)(rng);}

bool checa(colorUpdate& cc,vector<int>&teste){
  vector<int> t1(maxn);
  for(auto k:cc.ranges){
    for (int i=k.first;i<=k.second;i++)t1[i]=1;
  }
  for(int i=0;i<maxn;i++){
    if (teste[i]!=t1[i])return 0;
  }
  return 1;
}


signed main(){
  int cont=1;
  while(1){
    ofstream myfile;
    myfile.open ("t1.txt");
    vector<int> teste(maxn);
    colorUpdate cc;
    vector<pair<int,pair<int,int>>>casos(maxn);
    for(int i=0;i<maxn;i++){
      casos[i].first=rand()%2;
      casos[i].second.first=randint(0,maxn);
      casos[i].second.second=randint(0,maxn);
      if (casos[i].second.first>casos[i].second.second){
        swap(casos[i].second.first,casos[i].second.second);
      }
      myfile<<casos[i].first<<" "<<casos[i].second.first<<" "<<casos[i].second.second<<endl;
    }
    myfile.close();
    
    for(auto k:casos){
      if (k.first){
        cc.add(k.second.first,k.second.second);
        for(int i=k.second.first;i<=k.second.second;i++){
          teste[i]=1;
        }
      }
      else{
        cc.remove(k.second.first,k.second.second);
        for(int i=k.second.first;i<=k.second.second;i++){
          teste[i]=0;
        }
      }
      if (!checa(cc,teste)){
        cout<<"DEU MERDA"<<endl;
        return 0;
      }
    }
    
  }
  
}
