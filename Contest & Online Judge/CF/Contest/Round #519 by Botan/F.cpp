#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 9;
const int MX = 3e5 + 5;

int inve[MX], fact[MX];
int cnt[MX];
int mobius[MX];
bool prime[MX];
int n;

int modPow(int base, int po) {
  int ret = 1;
  while (po) {
    if (po & 1) ret = 1ll * ret * base % MOD;
    base = 1ll * base * base % MOD;
    po >>= 1;
  }
  return ret;
}

int C(int n, int k) {
  if (n < k) return 0;

  long long ret = fact[n];
  ret = ret * inve[k] % MOD;
  ret = ret * inve[n-k] % MOD;

  return ret;
}

void precompute() {
  fact[0] = inve[0] = 1;
  for (int i = 1 ; i < MX ; i++) {
    fact[i] = 1ll * i * fact[i-1] % MOD;
    inve[i] = modPow(fact[i], MOD-2);
  }

  for (int i = 1 ; i < MX ; i++) {
    mobius[i] = 1;
    prime[i] = 1;
  }

  prime[1] = 0;

  for (int i = 2 ; i < MX ; i++)
    if (prime[i]) {
      mobius[i] = -1;

      for (int j = i + i ; j < MX ; j += i) {
        prime[j] = 0;
        mobius[j] = -mobius[j];

        if (j % (1ll * i * i) == 0) {
          mobius[j] = 0;
        }
      }
    }
}

bool test(int k) {
  long long ret = 0;
  for (int i = 1 ; i < MX ; i++) {
    ret += 1ll * mobius[i] * C(cnt[i], k);
    ret %= MOD;
  }

  return ret != 0;
}

void init() {
  scanf("%d", &n);
  for (int i = 0 ; i < n ; i++) {
    int x; scanf("%d", &x);
    cnt[x]++;
  }

  for (int i = 1 ; i < MX ; i++)
    for (int j = i + i ; j < MX ; j += i)
      cnt[i] += cnt[j];
}

int work() {
  for (int i = 1 ; i <= 10 ; i++)
    if (test(i)) {
      return i;
    }
  return -1;
}

int main() {
  precompute();
  init();
  printf("%d\n", work());
  return 0;
}