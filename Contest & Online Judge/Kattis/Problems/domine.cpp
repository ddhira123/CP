#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const long long IMPOSSIBLE = 4e18 + 100;

int arr[N][3];
long long dp[N][N][8];
int n, k;

void read() {
  scanf("%d %d", &n, &k);
  for (int i = 0 ; i < n ; i++)
    for (int j = 0 ; j < 3 ; j++)
      scanf("%d", &arr[i][j]);
}

long long solve(int row, int left, int mask) {
  if (row == n) {
    assert(mask == 0);

    return left == 0 ? 0 : -IMPOSSIBLE;
  }

  long long &ret = dp[row][left][mask];
  if (ret != IMPOSSIBLE) return ret;

  ret = -IMPOSSIBLE;
  // ...
  ret = max(ret, solve(row+1, left, 0));

  {
    // --.
    if ((mask & 3) == 0 && left >= 1) ret = max(ret, solve(row+1, left-1, 0) + arr[row][0] + arr[row][1]);
    // .--
    if ((mask & 6) == 0 && left >= 1) ret = max(ret, solve(row+1, left-1, 0) + arr[row][1] + arr[row][2]);
  }

  if (row+1 < n) {
    for (int cur = 1 ; cur < 8 ; cur++) {
      int cnt = __builtin_popcount(cur);
      if ((mask & cur) == 0 && left >= cnt) {
        long long add = 0;
        for (int i = 0 ; i < 3 ; i++)
          if (cur & (1 << i))
            add += (arr[row][i] + arr[row+1][i]);
        ret = max(ret, solve(row+1, left-cnt, cur) + add);
      }
    }

    if (mask == 0 && left >= 2) {
      long long add = arr[row][0] + arr[row][1] + arr[row][2];
      ret = max(ret, solve(row+1, left-2, 1) + add + arr[row+1][0]);
      ret = max(ret, solve(row+1, left-2, 4) + add + arr[row+1][2]);
    }
  }

  return ret;
}

long long work() {
  for (int i = 0 ; i < N ; i++)
    for (int j = 0 ; j < N ; j++)
      for (int it = 0 ; it < 8 ; it++)
        dp[i][j][it] = IMPOSSIBLE;
  
  return solve(0, k, 0);
}

int main() {
  read();
  cout << work() << endl;
  return 0;
}