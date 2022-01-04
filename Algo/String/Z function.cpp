// z[i] = longest common prefix of the string starting at i and the beggining of the string;
// aaaaa = 0 4 3 2 1
// aaabaab = 0 2 1 0 2 1 0
vector<int> Z(string &s){
  int n=s.length();
  vector<int> z(n);
  for (int i=1,l=0,r=0;i<n;i++){
    if(i<r){
      z[i]=min(r-i,z[i-l]);
    }
    while(i+z[i]<n && s[i+z[i]]==s[z[i]]){
      z[i]++;
    }
    if ((i+z[i])>=r){
      l=i;
      r=i+z[i];
    }
  }
  return z;
}
