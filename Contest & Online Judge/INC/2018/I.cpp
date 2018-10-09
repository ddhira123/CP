#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
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

int n;
int arr[N];
int cnt[N];

int fact[N];
int inve[N];
int ans[N];

void precompute() {
  fact[0] = inve[0] = 1;
  for (int i = 1 ; i < N ; i++) {
    fact[i] = 1ll * i * fact[i-1] % MOD;
    inve[i] = modPow(fact[i], MOD-2); 
  }
}

long long getAns(int k) {
  if (ans[k] != -1) return ans[k];

  int&asd = ans[k];
  ans[k] = 0;
  int l = n-k;

  for (int i = 0 ; i <= l ; i++) {
    int ret = fact[l];
    ret = 1ll * ret * inve[l-i] % MOD;
    ret = 1ll * ret * k % MOD;
    ret = 1ll * ret * fact[n-i-1] % MOD;
    ret = 1ll * ret * i % MOD;

    // printf("k %d factl %d inveli %d factni %d i %d ret %d\n", k, fact[l], inve[l-i], fact[n-i-1], i, ret);
    asd = (asd + ret) % MOD;
  }

  // printf

  return asd;
}

int main() {
  precompute();
  memset(ans, -1, sizeof ans);

  scanf("%d", &n);
  // n = 100000;

  for (int i = 1 ; i <= n ; i++)
    for (int j = i ; j <= n ; j += i)
      cnt[j]++;

  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);
    // arr[i] = rand() % (1000000001);
  }

  long long sum = 0;
  for (int i = 1 ; i <= n ; i++) {
    sum += 1ll * arr[i] * getAns(cnt[i]);
    sum %= MOD;
  }

  // printf("sum %lld\n", sum);
  long long ret = sum * inve[n] % MOD;
  printf("%lld\n", ret);
  return 0;
}