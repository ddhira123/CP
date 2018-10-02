#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int K = 7;

int dp[N][N][K];
int arr[N];
int n,k;

int solve(int l, int r, int cnt) {
  int &ret = dp[l][r][cnt];
  if (ret != -1) return ret;

  ret = 1e9;

  // stop streak here
  if (l+1 <= r) {
    ret = min(ret, k - cnt + solve(l+1, r, 1));
  } else {
    ret = min(ret, k - cnt);
  }

  // continue streak
  for (int i = l+1 ; i <= r ; i++) {
    if (arr[i] == arr[l]) {
      int val = solve(i, r, min(k, cnt+1));
      if (i > l+1) val += solve(l+1, i-1, 1);

      ret = min(ret, val);
    }
  }

  // printf("%d %d %d dp %d\n", l, r, cnt, ret);
  return ret;
}

void read() {
  cin >> n >> k;
  for (int i = 1 ; i <= n ; i++)
    cin >> arr[i];
}

int main() {
  read();
  memset(dp, -1, sizeof dp);
  printf("%d\n", solve(1, n, 1));
  return 0;
}