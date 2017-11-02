#include <bits/stdc++.h>
using namespace std;

int pwr[100005];

int modPow(int base, int po, int mod) {
    int ret = 1ll % mod;

    while(po) {
        if(po & 1) ret = 1ll * ret * base % mod;
        base = 1ll * base * base % mod;
        po >>= 1;
    }

    return ret;
}

int solve(int n, int a, int p) {
    int ret = a % p;
    for(int i = 2 ; i <= n ; i++) {
        ret = modPow(ret, i, p);
    }
    return ret;
}

int main() {
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        int n, a, p;
        cin >> a >> n >> p;
        printf("Case #%d: %d\n", tc, solve(n, a, p));
    }
    return 0;
}