#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MX = 2e6 + 5;

int mod_pow(int base, int po) {
    int ret = 1;

    while(po) {
        if(po & 1) ret = 1ll * ret * base % MOD;
        base = 1ll * base * base % MOD;
        po >>= 1;
    }

    return ret;
}

int inverse(int x) {
    return mod_pow(x, MOD-2);
}

int fact[MX];

int get_comb(int n, int k) {
    if(n < k || n < 0 || k < 0) return 0;

    int ret = fact[n];
    ret = 1ll * ret * inverse(fact[k]) % MOD;
    ret = 1ll * ret * inverse(fact[n - k]) % MOD;

    return ret;
}

void precompute() {
    fact[0] = 1;
    for(int i = 1 ; i < MX ; i++) {
        fact[i] = 1ll * i * fact[i-1] % MOD;
    }
}

int solve(int r, int w, int d) {
    int ret = 0;

    for(int use = 0 ; use <= w+1 ; use++) {
        int r_cur = r - (d+1) * use;

        if(r_cur < 0) {
            break;
        }

        int val = get_comb(w+1, use);
        val = 1ll * val * get_comb(w + r_cur, w) % MOD;

        if(use & 1) ret = (ret - val + MOD) % MOD;
        else ret = (ret + val) % MOD;
    }

    return ret;
}

int main() {
    precompute();

    int r, w, d;
    cin >> r >> w >> d;

    cout << solve(r, w, d) << endl;
    return 0;
}