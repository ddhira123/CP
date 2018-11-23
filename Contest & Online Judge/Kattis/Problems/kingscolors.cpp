#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 2505;

int modPow(int base, int po) {
  int ret = 1;
  while (po) {
    if (po & 1) ret = 1ll * ret * base % MOD;
    po >>= 1;
    base = 1ll * base * base % MOD;
  }
  return ret;
}

int C[N][N];
int n, k;

int main() {
  cin >> n >> k;

  for (int i = 0 ; i <= k ; i++) {
    C[i][0] = 1;
    for (int j = 1 ; j <= i ; j++) {
      C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
    }
  }

  int ret = 0;
  for (int i = k ; i >= 2 ; i--) {
    int ways = i;
    ways = 1ll * ways * modPow(i-1, n-1) % MOD;
    ways = 1ll * ways * C[k][i] % MOD;

    int sign = (k - i) & 1 ? -1 : 1;
    ret = (ret + ways * sign) % MOD;
  }

  ret = (ret + MOD) % MOD;
  printf("%d\n", ret);
  return 0;
}