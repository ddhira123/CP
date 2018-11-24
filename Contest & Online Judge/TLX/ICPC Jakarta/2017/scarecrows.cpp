#include <bits/stdc++.h>
using namespace std;

const int R = 14;
const int C = 1005;
const int MOD = 1e9 + 7;

int columnMask[C];
int pwr[C];
int dp[C][2];
int r, c;

void read() {
  scanf("%d %d", &r, &c);
  char s[C+5];

  for (int i = 0 ; i < r ; i++) {
    scanf("%s", s);
    for (int j = 0 ; j < c ; j++)
      if (s[j] == '.')
        columnMask[j] |= (1 << i);
  }
}

int solve(int mask, int now, int covered) {
  if (now == c) return 1;

  int &ret = dp[now][covered];
  if (ret != -1) return ret;

  ret = 0;
  int active = __builtin_popcount(mask & columnMask[now]);
  
  // use current column
  ret = (ret + 1ll * (pwr[active]-1) * solve(mask, now+1, 1)) % MOD;

  // is covered
  if (covered) {
    ret = (ret + solve(mask, now+1, 0)) % MOD;
  }

  // printf("now %d covered %d ways %d\n", now, covered, ret);

  return ret;
}

int work() {
  pwr[0] = 1;
  for (int i = 1 ; i < C ; i++) {
    pwr[i] = 2ll * pwr[i-1] % MOD;
  }

  int ret = 0;
  for (int i = 0 ; i < (1 << r) ; i++) {
    memset(dp, -1, sizeof dp);

    int cur = solve(i, 0, 1);

    // printf("mask %d cur %d\n", i, cur);

    if ((r-__builtin_popcount(i)) % 2 == 1) ret = (ret - cur + MOD) % MOD;
    else ret = (ret + cur) % MOD;
  }
  return ret;
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}