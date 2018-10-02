#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int A = 505;

int dp[N][N][A];

int a[N];
int c[N];
int n, l;

int solve(int pos, int beg, int left) {
  if (left < 0 || beg < 0) return -1e9;
  if (pos == n) {
    if (beg > 0 || left > 0) return -1e9;
    return 0;
  }

  int &ret = dp[pos][beg][left];
  if (ret != -1) return ret;

  ret = solve(pos+1, beg, left);
  ret = max(ret, solve(pos+1, beg-1, left - a[pos]) + c[pos]);
  
  return ret;
}

void read() {
  cin >> n >> l;
  for(int i = 0 ; i < n ; i++) cin >> a[i];
  for(int i = 0 ; i < n ; i++) cin >> c[i];
}

double work() {
  memset(dp, -1, sizeof dp);
  double ret = 2e18;

  int sumA = accumulate(a, a + n, 0);
  int sumC = accumulate(c, c + n, 0);

  for(int i = 0 ; i <= sumA ; i++) {
    // maximize L bag
    int totC = solve(0, l, i);
    if (totC >= 0) {
      double val = 1ll * totC * (sumC - totC);
      val /= (i * (sumA - i));

      ret = min(ret, val);
    }

    // maximize N-L bag
    totC = solve(0, n-l, i);
    if (totC >= 0) {
      double val = 1ll * totC * (sumC - totC);
      val /= (i * (sumA - i));

      ret = min(ret, val);
    }
  }

  return ret;
}

int main() {
  read();
  printf("%.9lf\n", work());
  return 0;
}