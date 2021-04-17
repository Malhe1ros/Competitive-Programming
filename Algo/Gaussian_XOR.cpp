 
#define MAXN 1510
 
bitset<MAXN> base[MAXN];
bitset<MAXN> aux[MAXN];
 
int add(bitset<MAXN> &x){
	bitset<MAXN> auxX(0);
 
	for(int i = 0; i < MAXN; ++i){
		// checando pos i e pos i no vetor x
 
		if(x[i]){ // tenho bit ativo nessa posicao
			if(base[i][i]){ // tem um vetor nessa posicao
				x ^= base[i];
				auxX ^= aux[i];
				if(!x.any()) return -1;
			}else{ // adiciono
				base[i] = x;
				auxX[i] = 1;
				aux[i] = auxX;
				return i;
			}
		}
	}
	return -1;
}
 
bitset<MAXN> query(bitset<MAXN> &x){
	bitset<MAXN> ans(0);
	for(int i = 0; i < MAXN; ++i){
		// checando pos i e pos i no vetor x
		if(x[i] && base[i][i]){
			x ^= base[i];
			ans ^= aux[i];
		}
	}
	return (x.any()? bitset<MAXN>(0) : ans);
}