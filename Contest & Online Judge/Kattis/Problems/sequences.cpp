#include <bits/stdc++.h>
using namespace std;

const int MX = 5e5 + 5;
const int MOD = 1e9 + 7;

int mod_pow(int base, int po) {
    int ret = 1;

    while(po) {
        if(po & 1) ret = 1ll * ret * base % MOD;
        base = 1ll * base * base % MOD;
        po >>= 1;
    }

    return ret;
}

int fact[MX];
int pwr[MX];
int inve[MX];

int get_comb(int n, int k) {
    if(n < 0 || k < 0 || n < k) return 0;

    int ret = fact[n];
    ret = 1ll * ret * inve[k] % MOD;
    ret = 1ll * ret * inve[n-k] % MOD;

    return ret;
}

void precompute() {
    fact[0] = inve[0] = pwr[0] = 1;

    for(int i = 1 ; i < MX ; i++) {
        fact[i] = 1ll * fact[i-1] * i % MOD;
        pwr[i] = 2ll * pwr[i-1] % MOD;
    }

    inve[MX-1] = mod_pow(fact[MX-1], MOD-2);
    for(int i = MX-2 ; i >= 1 ; i--) {
        inve[i] = 1ll * inve[i+1] * (i+1) % MOD;
    }
}

int work(string s) {
    int qmark = 0;
    int zero = 0;

    for(char x : s) {
        qmark += (x == '?');
        zero += (x == '0');
    }

    int ret = 0;
    for(int i = 0 ; i < s.length() ; i++) {
        if(s[i] == '0') {
            ret = (ret + 1ll * pwr[qmark] * i) % MOD;
        } else if(s[i] == '?') {
            ret = (ret + 1ll * pwr[qmark-1] * i) % MOD;
        }
    }

    for(int i = 0 ; i <= qmark ; i++) {
        int displace = 1ll * (zero + i - 1) * (zero + i) / 2 % MOD;
        int ways = get_comb(qmark, i);
        int tot = 1ll * displace * ways % MOD;

        ret = (ret - tot + MOD) % MOD;
    }

    return ret;
}

int main() {
    precompute();
    
    string s; cin >> s;
    cout << work(s) << endl;
    return 0;
}