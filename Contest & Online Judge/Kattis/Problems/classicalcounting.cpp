#include <bits/stdc++.h>
using namespace std;

#define LD long double

const int MAXN = 3e5 + 5;
const int MOD = 1e6 + 7;

int PHI;

int fact[MAXN];
int inve[MAXN];
int pwr1[MAXN], pwr2[MAXN];

int modPow(int x, int po) {
    int ret = 1;
    while (po) {
        if (po & 1) ret = 1ll * ret * x % MOD;
        x = 1ll * x * x % MOD;
        po >>= 1;
    }
    return ret;
}

void precompute() {
    PHI = MOD;
    int mod = MOD;
    for (int i = 2 ; mod != 1 ; i++)
        if (mod % i == 0) {
            PHI = PHI / mod * (mod - 1);
            while (mod % i == 0) mod /= i;
        }
    fact[0] = inve[0] = 1;

    for (int i = 1 ; i < MAXN ; i++) {
        pwr1[i] = pwr1[i-1];
        pwr2[i] = pwr2[i-1];

        int x = i;
        while (x % 29 == 0) {
            pwr1[i]++;
            x /= 29;
        }
        while (x % 34483 == 0) {
            pwr2[i]++;
            x /= 34483;
        }

        fact[i] = 1ll * fact[i-1] * x % MOD;
        inve[i] = modPow(fact[i], PHI-1);
    }
}

int getComb(int n, int k) {
    if (n < 0 || k < 0 || n < k) return 0;
    
    int ret = fact[n];
    ret = 1ll * ret * inve[k] % MOD;
    ret = 1ll * ret * inve[n-k] % MOD;

    ret = 1ll * ret * modPow(29, pwr1[n] - pwr1[k] - pwr1[n-k]) % MOD;
    ret = 1ll * ret * modPow(34483, pwr2[n] - pwr2[k] - pwr2[n-k]) % MOD;

    return ret;
}

int solve(int n, int m, int k) {
    // for (int i = 2 ; i < MOD ; i++) if (MOD % i == 0) printf("cuk %d\n", i);
    int ret = 0;
    for (int i = 0 ; i <= n ; i++) {
        int sisa = k - i * (m+1);
        if (sisa < 0) break;

        int val = 1ll * getComb(n, i) * getComb(sisa + n - 1, n - 1) % MOD;
        if (i  & 1) ret = (ret + MOD - val) % MOD;
        else ret = (ret + val) % MOD;
    }
    return ret;
}

int main() {
  precompute();  
  int n, m, k; cin >> n >> m >> k;

  long long ret = solve(n, m, k);
  cout << ret << endl;
  return 0;
}