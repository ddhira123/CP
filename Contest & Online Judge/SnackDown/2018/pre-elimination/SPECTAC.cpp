#include <bits/stdc++.h>
using namespace std;

const int N = 55;

int n, m, k, mod;
int C[N * N][N * N];
int dp[N][N][N][N];

int solve(int curEnd, int interval, int total, int last) {
  if (total < 0) return 0;

  if (curEnd > n) {
    return interval == 0 && total == 0;
  }

  int &ret = dp[curEnd][interval][total][last];
  if (ret != -1 ) return ret;

  // skip this end
  ret = solve(curEnd+1, interval, total, last);

  // use i interval
  for (int i = 1 ; i <= min(curEnd, interval) ; i++) {
    int kiri = last, kanan = curEnd - last;

    // all are below (<= last)
    if (i <= kiri) {
      ret = (ret + 1ll * C[kiri][i] * solve(curEnd+1, interval - i, total, last)) % mod;
    }

    // at least one is > last
    {
      int cur = C[curEnd][i];
      if (i <= kiri) {
        cur  = (cur - C[kiri][i] + mod) % mod;
      }

      ret = (ret + 1ll * cur * solve(curEnd+1, interval-i, total-1, curEnd)) % mod;
    }
  }

  return ret;
}

int main() {
  cin >> n >> m >> k >> mod;

  for (int i = 0 ; i < N*N ; i++) {
    C[i][0] = 1;
    for (int j = 1 ; j <= i ; j++) {
      C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
    }
  }

  memset(dp, -1, sizeof dp);
  cout << solve(1, m, k, 0) << endl;
  
  return 0;
}