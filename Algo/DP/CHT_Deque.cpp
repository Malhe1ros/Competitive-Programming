/*
Implementation of the convex hull trick for sorted queries and functions;
*/
struct cht{
    deque<pair<int,int>> deq;
    /*
    returns the int value of the intersection between 2 linear functions;
    */
    int inter(pair<int,int>a,pair<int,int>b){
        return (a.second-b.second)/(b.first-a.first);
    }
    /*
    used to add a line to the convex hull;
    [Consider lines in decreasing order]
    change sign for increasing
    */
    void add(pair<int,int> a){
        while(deq.size()>=2 && inter(deq.back(),a)<=inter(deq.back(),deq[deq.size()-2]))deq.pop_back();
        deq.push_back(a);
    }
    /*
    return the value of f(x);
    */
    int valor(pair<int,int>& f,int x){
        return f.first*x+f.second;
    }
    /*
    queries the maximum at the point x;
    [Consider queries in increasing order]
    change sign for decreasing
    */

    int query(int x){
        while(deq.size()>=2 && valor(deq.front(),x)>=valor(deq[1],x))deq.pop_front();
        return valor(deq.front(),x);
    }
};
