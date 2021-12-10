#include <bits/stdc++.h>
 
using namespace std;
 
//You will have to augment this in most of the problems
struct Node{
    map<char,int> nxt;
};

struct Trie{
    vector<Node> nodes;
    Trie(){
        nodes.push_back(Node());
    }

    void add(string &s,int i,int ind){
        if (i==s.length()) return;
        if (nodes[ind].nxt[s[i]]==0){
            nodes[ind].nxt[s[i]]=nodes.size();
            nodes.push_back(Node());
        }
        add(s,i+1,nodes[ind].nxt[s[i]]);
    }

    void add(string &s){
        s+='$';
        add(s,0,0);
    }

    bool find(string &s,int i,int ind){
        if (i==s.length()) return 1;
        if (nodes[ind].nxt[s[i]]==0)return 0;
        return find(s,i+1,nodes[ind].nxt[s[i]]);
    }

    bool find(string s){
        s+='$';
        return find(s,0,0);
    }
};


signed main(){
   Trie T;
   
   
}
