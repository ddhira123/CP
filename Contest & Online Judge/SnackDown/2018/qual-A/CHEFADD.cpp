#include <bits/stdc++.h>
using namespace std;

const int LOG = 31;

int a, b, c;
long long dp[LOG][LOG][LOG][2];

long long solve(int now, int bitA, int bitB, int carry) {
  if (bitA < 0 || bitB < 0) return 0;
  if ((1 << now) > c) return bitA + bitB + carry == 0;

  long long &ret = dp[now][bitA][bitB][carry];
  if (ret != -1) return ret;

  ret = 0;
  int active = (c & (1 << now)) != 0;

  for (int i = 0 ; i < 2 ; i++)
    for (int j = 0 ; j < 2 ; j++) {
      int tot = i + j + carry;
      if (tot % 2 == active) {
        ret += solve(now+1, bitA-i, bitB-j, tot / 2);
      }
    }
  
  return ret;
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    cin >> a >> b >> c;
    // a = rand() % 500000000 + 1;
    // b = rand() % 500000000 + 1;
    // c = a + b;

    memset(dp, -1, sizeof dp);
    cout << solve(0, __builtin_popcount(a), __builtin_popcount(b), 0) << endl;
  }
  return 0;
}