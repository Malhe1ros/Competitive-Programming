struct kthSum{
    int k;
    multiset<int> grandes;
    multiset<int,greater<int>> pequenos;
    int soma = 0;
    kthSum(int maxi){
        k = maxi;
    }
    void adiciona(int x){
        if(sz(grandes)<k){
            grandes.insert(x);
            soma+=x;
            return;
        }
 
        int teste = *grandes.begin();
        grandes.erase(grandes.begin());
        soma-=teste;
 
        if(x<teste)swap(x,teste);
 
        grandes.insert(x);
        soma+=x;
 
        pequenos.insert(teste);
 
    }
 
    void remova(int x){
        if(pequenos.find(x)!=pequenos.end()){
            pequenos.erase(pequenos.find(x));
            return;
        }
        assert(grandes.find(x)!=grandes.end());
 
        grandes.erase(grandes.find(x));
        soma-=x;
        if(!pequenos.empty()){
            int topo = *pequenos.begin();
            pequenos.erase(pequenos.find(topo));
 
            grandes.insert(topo);
            soma+=topo;
        }
    }
 
    int sumOfKGreatest(){
        return soma;
    }
 
};
