#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int MOD = 1e9 + 7;

int dp[N][2];

int solve(int sisa, int mod) {
    if(sisa == 0) {
        return mod == 0;
    }

    int &ret = dp[sisa][mod];
    if(ret != -1) return ret;

    ret = 2 * solve(sisa-1, mod) % MOD;
    ret = (ret + solve(sisa-1, mod^1)) % MOD;
    return ret;
}

int main() {
    memset(dp, -1, sizeof dp);
    int n; cin >> n;
    cout << solve(n, 0) << endl;
    return 0;
}