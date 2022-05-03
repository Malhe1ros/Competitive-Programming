template<typename T>
int LIS(T & arr)
{
    T ans;
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        auto it
            = lower_bound(ans.begin(), ans.end(), arr[i]);
        if (it == ans.end()) {
            ans.push_back(arr[i]);
        }
        else {
            *it = arr[i];
        }
    }
    return ans.size();
}
