#include <bits/stdc++.h>

using namespace std;

struct DSU{
    int* arr;
    DSU(int size){
        arr = new int[size];
        
        for (int i=0;i<size;i++){
            arr[i]=-1;
        }
    }
    int find(int a){
        int ac=a;
        while(arr[a]>=0){
            a=arr[a];
        }
        while(arr[ac]>=0){
            int cop=arr[ac];
            arr[ac]=a;
            ac=cop;
        }

        return a;
    }
    void unir(int a,int b){
        int paia=find(a);
        int paib=find(b);
        if (paia==paib) return;
        int tam=arr[paia]+arr[paib];
        if (arr[paia]>arr[paib]){
            arr[paia]=paib;
            arr[paib]=tam;
        }
        else{
            arr[paib]=paia;
            arr[paia]=tam;
        }
    }
};



int main(){
    DSU d = DSU(8);

    d.unir(0,1);

    d.unir(2,3);

    d.unir(4,5);

    d.unir(1,4);

    d.unir(0,1);
    for (int i=0;i<8;i++){
        cout<<d.arr[i]<<" ";
    }
    cout<<endl;
    d.unir(0,3);
    for (int i=0;i<8;i++){
        cout<<d.arr[i]<<" ";
    }
    cout<<endl;
    d.unir(0,7);
    for (int i=0;i<8;i++){
        cout<<d.arr[i]<<" ";
    }
    cout<<endl;
    d.unir(6,7);
    for (int i=0;i<8;i++){
        cout<<d.arr[i]<<" ";
    }
    cout<<endl;

}
