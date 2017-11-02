#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;

int modPow(int base, int po, int mod) {
    base %= mod;
    int ret = 1 % mod;

    while(po) {
        if(po & 1) {
            ret = 1ll * ret * base % mod;
        }

        base = 1ll * base * base % mod;
        po >>= 1;
    }

    return ret;
}

int arr[N];
int n, k;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", arr + i);
    }
}

int solve() {
    k = modPow(2, k, MOD-1);

    int ret = arr[0];
    ret = 1ll * ret * modPow(n, k, MOD) % MOD;
    
    return ret;
}

int main() {
    read();
    printf("%d\n", solve());
    return 0;
}
