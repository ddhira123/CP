#include <bits/stdc++.h>
using namespace std;

int mod_pow(int base, int po, int mod) {
    int ret = 1 % mod;
    while(po) {
        if(po & 1) ret = 1ll * ret * base % mod;
        base = 1ll * base * base % mod;
        po >>= 1;
    }
    return ret;
}

int calc_same(int n, int mod) {
    if(n % 2 != 0) return 0;
    int ret = 1;

    int pwr = 0;

    int k = n / 2;
    for(int i = n ; i > k ; i--) {
        int j = i;

        while(j % mod == 0) {
            j /= mod;
            pwr++;
        }

        ret = 1ll * ret * j % mod;
    }

    int bawah = 1;
    for(int i = 1 ; i <= k ; i++) {
        int j = i;
        while(j % mod == 0) {
            j /= mod;
            pwr--;
        }

        bawah = 1ll * bawah * j % mod;
    }

    ret = 1ll * ret * mod_pow(bawah, mod-2, mod) % mod;
    ret = 1ll * ret * mod_pow(mod, pwr, mod) % mod;

    // cout << "sama " << ret << endl;
    return ret;
}

int dp[1000005][2];

int calc_diff(int n, int mod) {
    dp[1][0] = 1;
    dp[1][1] = 1;

    for(int i = 2 ; i <= n ; i++) {
        dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % mod;
        dp[i][1] = dp[i-1][0];
    }

    return (dp[n][0] + dp[n][1]) % mod;
}

int calc_diff_and_same(int n, int mod) {
    if(n % 2 != 0) return 0;

    dp[1][0] = 1;
    dp[1][1] = 1;

    for(int i = 2 ; i <= n / 2 ; i++) {
        dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % mod;
        dp[i][1] = dp[i-1][1];
    }

    return (dp[n / 2][0] + dp[n / 2][1]) % mod;
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        int n, mod;
        cin >> n >> mod;

        int ret = (calc_same(n, mod) + calc_diff(n, mod)) % mod;
        ret = (ret - calc_diff_and_same(n, mod) + mod) % mod;

        cout << ret << endl;
    }
    return 0;
}