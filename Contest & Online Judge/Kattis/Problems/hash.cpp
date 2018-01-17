#include <bits/stdc++.h>
using namespace std;

const int M = 25;

int mod_pow(int base, int po, int mod) {
    base %= mod;
    int ret = 1 % mod;

    while(po) {
        if(po & 1) ret = 1ll * ret * base % mod;
        base = 1ll * base * base % mod;
        po >>= 1;
    }

    return ret;
}

int cnt[1 << M];
int n, k, m;
int inverse, mask;

void forward_rec(int left, int val) {
    if(left == 0) {
        cnt[val]++;
    } else {
        int nval = val * 33;

        for(int i = 1 ; i <= 26 ; i++) {
            forward_rec(left-1, (nval ^ i) & mask);
        }
    }
}

long long backward_rec(int left, int val) {
    if(left == 0) {
        return cnt[val];
    } else {
        long long ret = 0;

        for(int i = 1 ; i <= 26 ; i++) {
            int nval = val ^ i;
            nval = (1ll * nval * inverse) & mask;

            ret += backward_rec(left-1, nval);
        }

        return ret;
    }
}

int main() {
    cin >> n >> k >> m;

    mask = (1 << m) - 1;
    inverse = mod_pow(33, (1 << (m-1)) - 1, 1 << m);

    forward_rec(n / 2, 0);
    long long ret = backward_rec(n - n / 2, k);

    cout << ret << endl;
    return 0;
}