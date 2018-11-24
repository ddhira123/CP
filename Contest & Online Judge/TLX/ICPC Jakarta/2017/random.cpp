#include <bits/stdc++.h>
using namespace std;

const int N = 3005;

double dp[N][N];

void precompute() {
  dp[0][0] = 0;
  for (int zero = 0 ; zero < N ; zero++)
    for (int one = 0 ; one < N ; one++) {
      if (zero == 0 && one == 0) continue;

      dp[zero][one] = 1.0 / (zero + one);
      if (zero > 0) dp[zero][one] += 1.0 * zero / (zero + one) * dp[zero-1][one+1];
      if (one > 0) dp[zero][one] += 1.0 * one / (one + zero) * dp[zero][one-1];
    }
}

int main() {
  precompute();
  int t; scanf("%d", &t);

  for (int tc = 1 ; tc <= t ; tc++) {
    map<int, int> cnt;
    int n, k;

    scanf("%d %d", &n, &k);
    for (int i = 0 ; i < k ; i++) {
      int x; scanf("%d", &x);
      cnt[x]++;
    }

    int two = 0;
    int one = 0;
    int zero = 0;

    for (auto it : cnt) {
      if (it.second >= 2) two++;
      else one++;
    }

    zero = n - two - one;
    double ret = dp[zero][one] * n;

    printf("%.9lf\n", ret);
  }
  return 0;
}