#include <bits/stdc++.h>
using namespace std;

const int N = 400005;
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

int fact[N];
int inve[N];
int pwr[N];

void precompute() {
  fact[0] = 1;
  for (int i = 1 ; i < N ; i++) {
    fact[i] = 1ll * i * fact[i-1] % MOD;
  }
  // for (int i = 0 ; i < 5 ; i++) cout << i << " " << fact[i] << endl;
  inve[N-1] = modPow(fact[N-1], MOD-2);

  for (int i = N-2 ; i >= 0 ; i--) {
    inve[i] = 1ll * (i+1) * inve[i+1] % MOD;
  }

  pwr[0] = 1;
  for (int i = 1 ; i < N ; i++) {
    pwr[i] = 2ll * pwr[i-1] % MOD;
  }
}

int getComb(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;

  int ret = fact[n];
  ret = 1ll * ret * inve[k] % MOD;
  ret = 1ll * ret * inve[n-k] % MOD;

  // printf("n %d k %d ret %d\n", n, k, ret);
  return ret;
}

int solve(int n, int m) {
  int ret = 0;
  for (int i = 0 ; i <= m ; i++) {
    int ways = getComb(m, i);
    ways = 1ll * ways * fact[2*n - i] % MOD;
    ways = 1ll * ways * pwr[i] % MOD;
    // printf("f %d\n", fact[2 * n]);

    // printf("i %d ways %d\n", i, ways);

    if (i % 2 == 0) ret = (ret + ways) % MOD;
    else ret = (ret + MOD - ways) % MOD;
  }
  return ret;
}

int main() {
  precompute();

  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    int n, m;
    cin >> n >> m;

    printf("Case #%d: %d\n", tc, solve(n, m));
  }
  return 0;
}