#include <bits/stdc++.h>
using namespace std;

long long n;

int vals[65];
long long dp[65][2][2][2];
int len;

int isZero(int a, int b) {
  return b > a;
}

long long solve(int now, int zero, int isLess, int isLess2) {
  if (now < 0) return !zero;

  long long &ret = dp[now][zero][isLess][isLess2];
  if (ret != -1) {
    return ret;
  }
  ret = 0;

  int lmt1 = 1;
  if (!isLess) lmt1 = vals[now];

  for (int i = 0 ; i <= lmt1 ; i++) {
    int lmt2 = 1;
    if (!isLess2) lmt2 = i;

    for (int j = 0 ; j <= lmt2 ; j++) {
      int nzero = isZero(i, j) || zero;
      int nless1 = isLess || (i < vals[now]);
      int nless2 = isLess2 || (j < i);

      ret += solve(now-1, nzero, nless1, nless2);
    } 
  }

  return ret;
}

int main() {
  cin >> n;
  n--;
  while (n > 0) {
    vals[len++] = n % 2;
    n /= 2;
  }

  memset(dp, -1, sizeof dp);
  cout << solve(len-1, 0, 0, 0) << endl;
  return 0;
}