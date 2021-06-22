 #include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

//to avoid hacking but when offline not necessary
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};

gp_hash_table<int,int,chash> mapa;

int main(){

}
