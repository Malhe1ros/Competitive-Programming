#include <bits/stdc++.h>
using namespace std;
void induced_sort(const vector<int>& vec, int val_range, vector<int>& SA, const vector<bool>& sl, const vector<int>& lms_idx) {
  vector<int> l(val_range, 0), r(val_range, 0);
  for (int c : vec) {
    if (c + 1 < val_range) ++l[c + 1];
    ++r[c];
  }
  partial_sum(l.begin(), l.end(), l.begin());
  partial_sum(r.begin(), r.end(), r.begin());
  fill(SA.begin(), SA.end(), -1);
  for (int i = lms_idx.size() - 1; i >= 0; --i) SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
  for (int i : SA) if (i >= 1 && sl[i - 1]) SA[l[vec[i - 1]]++] = i - 1;
  fill(r.begin(), r.end(), 0);
  for (int c : vec) ++r[c];
  partial_sum(r.begin(), r.end(), r.begin());
  for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k]) if (i >= 1 && !sl[i - 1]) SA[--r[vec[i - 1]]] = i - 1;
}
vector<int> SA_IS(const vector<int>& vec, int val_range) {
  const int n = vec.size();
  vector<int> SA(n), lms_idx;
  vector<bool> sl(n);
  sl[n - 1] = false;
  for (int i = n - 2; i >= 0; --i) {
    sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
    if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
  }
  reverse(lms_idx.begin(), lms_idx.end());
  induced_sort(vec, val_range, SA, sl, lms_idx);
  vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
  for (int i = 0, k = 0; i < n; ++i) if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) new_lms_idx[k++] = SA[i];
  int cur = 0;
  SA[n - 1] = cur;
  for (size_t k = 1; k < new_lms_idx.size(); ++k) {
    int i = new_lms_idx[k - 1], j = new_lms_idx[k];
    if (vec[i] != vec[j]) {
      SA[j] = ++cur;
      continue;
    }
    bool flag = false;
    for (int a = i + 1, b = j + 1;; ++a, ++b) {
      if (vec[a] != vec[b]) {
        flag = true;
        break;
      }
      if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
        flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
        break;
      }
    }
    SA[j] = (flag ? ++cur : cur);
  }
  for (size_t i = 0; i < lms_idx.size(); ++i) lms_vec[i] = SA[lms_idx[i]];
  if (cur + 1 < (int)lms_idx.size()) {
    auto lms_SA = SA_IS(lms_vec, cur + 1);
    for (size_t i = 0; i < lms_idx.size(); ++i) {
      new_lms_idx[i] = lms_idx[lms_SA[i]];
    }
  }
  induced_sort(vec, val_range, SA, sl, new_lms_idx);
  return SA;
}
vector<int> suffix_array(const string& s, const int LIM = 128) {
  vector<int> vec(s.size() + 1);
  copy(begin(s), end(s), begin(vec));
  vec.back() = '$';
  auto ret = SA_IS(vec, LIM);
  ret.erase(ret.begin());
  return ret;
}
vector<int> LCP(const string& s, const vector<int>& sa) {
  int n = (int)s.size(), k = 0;
  vector<int> lcp(n), rank(n);
  for (int i = 0; i < n; i++) rank[sa[i]] = i;
  for (int i = 0; i < n; i++, k ? k-- : 0) {
    if (rank[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = sa[rank[i] + 1];
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
    lcp[rank[i]] = k;
  }
  lcp[n - 1] = 0;
  return lcp;
}

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  string s; cin >> s;
  vector<int> sa = suffix_array(s);//return without the '$' position;
  vector<int> lcp = LCP(s, sa);//returns the lcp[0] = lcp(position 2, position 1);

  //exaple string: abababa
  for(auto k:sa){
    cout<<k<<" ";
  }
  cout<<endl;
  /*
    in sa we have:
    a - 6
    aba - 4
    ababa - 2
    abababa - 0
    ba - 5
    baba - 3
    bababa - 1
  */
  for(auto k:lcp){
    cout<<k<<" ";
  }
  cout<<endl;
  /*
    [1,3,5,0,2,4,0];
    in first position, the lcp between "aba" and "a";
  */
  return 0;
}
