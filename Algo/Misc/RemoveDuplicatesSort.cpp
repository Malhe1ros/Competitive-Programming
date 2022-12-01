void removeDuplicatesAndSort(vector<int>&v){
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
}
