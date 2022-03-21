/*
    -1 if angle(A,B) < angle(B,C);
     0 if angle(A,B) == angle(B,C);
    +1 if angle(A,B) > angle(B,C);
*/
int compara(PV a,PV b,PV c){
    int dotAB=dot(a,b);
    int dotBC=dot(b,c);
    int sgnAB=sgn(dotAB);
    int sgnBC=sgn(dotBC);
    if(sgnAB==sgnBC){
        int l=dotAB*dotAB*norma(c);//norma(c)=dot(c,c)
        int r=dotBC*dotBC*norma(a);
        if(l==r)return 0;
        if(sgnAB==1)return (l>r) ? -1:1;
        return (l<r) ? -1:1; 
    }
    if(sgnAB>sgnBC)return -1;
    return 1;
}
