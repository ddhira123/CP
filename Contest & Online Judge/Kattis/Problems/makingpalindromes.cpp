#include <bits/stdc++.h>
using namespace std;

const int N = 205;
const int MOD = 1e9 + 7;

string s;
int n;

int dp[N][N][N];

int solve(int sisa, int l, int r) {
  if (l > r) {
    int ret = 1;
    for (int i = 0 ; i < sisa ; i++) ret = 1ll * ret * 26 % MOD;
    return ret;
  }
  if (sisa == 0) return 0;

  int &ret = dp[sisa][l][r];
  if (ret != -1) return ret;

  ret = 0;
  for (int i = 'A' ; i <= 'Z' ; i++) {
    int nl = s[l] == i ? l+1 : l;
    int nr = s[r] == i ? r-1 : r;
    ret = (ret + solve(sisa-1, nl, nr)) % MOD;
  }

  return ret;
}

int main() {
  cin >> n >> s;
  // n = 200;
  // s = "";
  // for (int i = 0 ; i < n ; i++) s += (char)('A' + rand() % 26);
  memset(dp, -1, sizeof dp);

  cout << solve(n, 0, n-1) << endl;
  return 0;
}