#include <bits/stdc++.h>
using namespace std;

const int N = 16;
const int ALPHA = 26;

int cnt[1 << N][ALPHA];
int sums[1 << N];
int dp[1 << N];
int n;

int solve(int mask) {
  int &ret = dp[mask];
  if(ret != -1) return ret;

  if(mask == (mask & -mask)) {
    return ret = sums[mask];
  }

  ret = 1e9;
  for(int i = mask & (mask-1) ; i > 0 ; i = mask & (i - 1)) {
    int j = mask ^ i;

    ret = min(ret, solve(i) + solve(j) - sums[mask]);
  }

  return ret;
}

void read() {
  cin >> n;
  for(int i = 0 ; i < n ; i++) {
    string s; cin >> s;
    for(char x : s)
      cnt[1 << i][x - 'a']++;
  }
}

void prepare() {
  for(int i = 1 ; i < (1 << n) ; i++) {
    int lsb = i & -i;
    if (lsb != i) {
      for(int j = 0 ; j < ALPHA ; j++)
        cnt[i][j] = min(cnt[lsb][j], cnt[i - lsb][j]);
    }

    sums[i] = accumulate(cnt[i], cnt[i] + ALPHA, 0);
  }
  memset(dp, -1, sizeof dp);
}

int main() {
  read();
  prepare();
  printf("%d\n", 1 + solve((1 << n)-1));
  return 0;
}