#include <bits/stdc++.h>
using namespace std;

const int M = 105;
const int K = 505;

long long dp[M][K];
int cnt[M];

int n, m, k;

long long calc(int size) {
  return 1ll * size * (size + 1) / 2;
}

long long getVal(int val, int k) {
  int part = val / (k + 1);
  int sisa = val % (k + 1);

  return sisa * calc(part+1) + (k+1-sisa) * calc(part);
}

long long solve(int pos, int left) {
  if(pos > m) return 0;

  long long &ret = dp[pos][left];
  if (ret != -1) return ret;

  ret = 4e18;
  for(int i = 0 ; i <= left ; i++) {
    ret = min(ret, getVal(cnt[pos], i) + solve(pos+1, left-i));
  }

  return ret;
}

void read() {
  scanf("%d %d %d", &n, &m, &k);
  for(int i = 0 ; i < n ; i++) {
    int x; scanf("%d", &x);
    cnt[x]++;
  }
}

int main() {
  read();
  memset(dp, -1, sizeof dp);
  printf("%lld\n", solve(1, k));
  return 0;
}