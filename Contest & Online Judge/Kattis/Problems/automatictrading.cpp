#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int BASE = 97;
const int N = 1e5 + 5;

int convert(char x) {
    if('a' <= x && x <= 'z') return x - 'a' + 1;
    return 27 + x - 'A';
}

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

char s[N];
int psum[N];
int pwr[N];
int inve[N];
int len;

int get_hash(int l, int r) {
    int ret = psum[r];

    if(l) {
        ret = (ret - psum[l-1] + MOD) % MOD;
        ret = 1ll * ret * inve[l] % MOD;
    }

    return ret;
}

void read() {
    scanf("%s", s);
}

void prepare() {
    len = strlen(s);

    pwr[0] = inve[0] = 1;
    psum[0] = convert(s[0]);

    for(int i = 1 ; i < len ; i++) {
        pwr[i] = 1ll * pwr[i-1] * BASE % MOD;
        inve[i] = inverse(pwr[i]);
        psum[i] = (psum[i-1] + 1ll * pwr[i] * convert(s[i])) % MOD;
    }
}

int solve(int a, int b) {
    if(a > b) swap(a, b);
    int lo = 0, hi = len - b;

    while(lo < hi) {
        int mid = (lo + hi + 1) / 2;

        if(get_hash(a, a+mid-1) == get_hash(b, b+mid-1)) {
            lo = mid;
        } else {
            hi = mid-1;
        }
    }

    return lo;
}

void work() {
    int q; scanf("%d", &q);

    for(int i = 0 ; i < q ; i++) {
        int l, r;
        scanf("%d %d", &l, &r);

        printf("%d\n", solve(l, r));
    }
}

int main() {
    read();
    prepare();
    work();
    return 0;
}