#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int MOD = 1e9 + 7;

int modPow(int base, int po) {
    int ret = 1;
    while (po) {
        if (po & 1) ret = 1ll * ret * base % MOD;
        base = 1ll * base * base % MOD;
        po >>= 1;
    }
    return ret;
}

int arr[N];
int dp[N][N];

int solve(int now, int k) {
    if (k == 0) return 1;
    if (now == 0) return 0;
    
    int &ret = dp[now][k];

    if (ret != -1) return ret;
    ret = solve(now-1, k);
    ret = (ret + 1ll * arr[now] * solve(now-1, k-1)) % MOD;

    return ret;
}

int main() {
    // double ret = 0;
    // for (int i = 1 ; i <= 100 ; i++)
    //     ret += 1.0 / (i * i);
    // cout << ret << endl;
    memset(dp, -1, sizeof dp);
    int n; cin >> n;

    for (int i = 1 ; i <= n ; i++) {
        printf("1 1 %d\n", i);
        fflush(stdout);

        int k, s; scanf("%d %d", &k, &s);
        s = (s + MOD - solve(i-1, k)) % MOD;
        s = (1ll * s * modPow(solve(i-1, k-1), MOD-2)) % MOD;

        arr[i] = s;
    }

    printf("2");
    for (int i = 1 ; i <= n ; i++)
        printf(" %d", arr[i]);
    printf("\n");
    fflush(stdout);
    return 0;
}