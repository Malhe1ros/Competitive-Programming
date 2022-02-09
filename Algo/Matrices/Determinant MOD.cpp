#include <bits/stdc++.h>

using namespace std;

int p;

int sub(int a, int b) {
    return a - b + (a < b ? p : 0);
}
int mul(int a, int b) {
    return 1LL * a * b % p;
}

const int maxn = 501;
int a[maxn][maxn];

int det(int i, int n) {
    if(i == n) {
        return 1 % p;
	}
    int tmp = 1;
    for(int j = i + 1; j < n; j++) {
        while(a[j][i]) {
            tmp = p - tmp;
            int c = a[i][i] / a[j][i];
            for(int k = i; k < n; k++) {
                a[i][k] = sub(a[i][k], mul(a[j][k], c));
                swap(a[i][k], a[j][k]);
            }
        }
    }
    return mul(tmp, mul(a[i][i], det(i + 1, n)));
}

signed main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n >> p;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    cout << det(0, n) << "\n";
}
